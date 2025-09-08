/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiReactor.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:34:48 by zsailine          #+#    #+#             */
/*   Updated: 2025/09/08 10:19:15 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiReactor.hpp"
#include <sys/epoll.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sstream> 

CgiReactor& CgiReactor::instance() {
    static CgiReactor g;
    return g;
}

void CgiReactor::setNonBlocking_(int fd) {
    int fl = fcntl(fd, F_GETFL, 0);
    if (fl != -1) fcntl(fd, F_SETFL, fl | O_NONBLOCK);
}

void CgiReactor::setCloExec_(int fd) {
    int flags = fcntl(fd, F_GETFD);
    if (flags != -1) fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
}

bool CgiReactor::isCgiFd(int fd) const 
{
    bool found = (_byFd.find(fd) != _byFd.end());
    return found;
}

void CgiReactor::registerJob(int epfd, CgiJob* job) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));

    // cgi_out: lecture
    setNonBlocking_(job->cgi_out);
    setCloExec_(job->cgi_out);
    ev.data.fd = job->cgi_out;
    ev.events  = EPOLLIN | EPOLLERR | EPOLLHUP;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, job->cgi_out, &ev) < 0) {
        perror("epoll_ctl ADD cgi_out");
    }
    _byFd[job->cgi_out] = job;

    // cgi_in: écriture (si POST)
    if (job->cgi_in >= 0) 
    {
        memset(&ev, 0, sizeof(ev));
        setNonBlocking_(job->cgi_in);
        setCloExec_(job->cgi_in);
        ev.data.fd = job->cgi_in;
        ev.events  = EPOLLOUT | EPOLLERR | EPOLLHUP;
        epoll_ctl(epfd, EPOLL_CTL_ADD, job->cgi_in, &ev);
        _byFd[job->cgi_in] = job;
    }
}

bool CgiReactor::childIsDone_(pid_t pid) {
    int st = 0;
    pid_t r = waitpid(pid, &st, WNOHANG);
    if (r == pid) 
        return true;
    return false;
}

void CgiReactor::parseCgiHeaders_(CgiJob* job) {
    std::string::size_type p = job->out_buf.find("\r\n\r\n");
    if (p == std::string::npos) return;
    std::string headers = job->out_buf.substr(0, p);
    std::string body    = job->out_buf.substr(p + 4);

    std::string::size_type s = headers.find("Status:");
    if (s != std::string::npos) {
        std::string::size_type e = headers.find("\r\n", s);
        std::string line = (e == std::string::npos) ? headers.substr(s) : headers.substr(s, e - s);
        std::string::size_type colon = line.find(':');
        if (colon != std::string::npos) {
            std::string val = line.substr(colon + 1);
            while (!val.empty() && (val[0]==' ' || val[0]=='\t')) val.erase(0,1);
            job->status_code = atoi(val.c_str());
        }
        std::string::size_type lb = (s == 0) ? 0 : headers.rfind("\r\n", s);
        if (lb == std::string::npos) lb = 0; else lb += 2;
        std::string::size_type le = headers.find("\r\n", s);
        if (le == std::string::npos) headers.erase(lb);
        else headers.erase(lb, le + 2 - lb);
    }
    job->http_body = body;
    job->http_headers = headers + "\r\n";
    job->headers_done = true;
}

void CgiReactor::finalize_(int epfd, CgiJob* job, Request& req) 
{
    if (job->cgi_out >= 0) {
        delEpollEvent(epfd, job->cgi_out);
        close(job->cgi_out);
        _byFd.erase(job->cgi_out);
        job->cgi_out = -1;
    }
    if (job->cgi_in >= 0) {
        delEpollEvent(epfd, job->cgi_in);
        close(job->cgi_in);
        _byFd.erase(job->cgi_in);
        job->cgi_in = -1;
    }

    parseCgiHeaders_(job);
    if (!job->headers_done) {
        job->status_code = 502;
        job->http_headers.clear();
        job->http_body = "Bad Gateway";
    }
    
    std::string statusLine = "HTTP/1.1 ";
    switch (job->status_code) {
        case 200: statusLine += "200 OK\r\n"; break;
        case 403:  statusLine += "403 Forbidden\r\n"; 
                   job->http_body = readFile(req.getError(403));
                   break;
        case 404: statusLine += "404 Not Found\r\n"; 
                job->http_body = readFile(req.getError(404));
                break;
        case 500: statusLine += "500 Internal Server Error\r\n"; 
                job->http_body = readFile(req.getError(500));
                break;
        case 502: statusLine += "502 Bad Gateway\r\n"; 
                job->http_body = readFile(req.getError(502));
                break;
        default: {
            std::ostringstream oss; oss << job->status_code;
            statusLine += oss.str() + " Error\r\n";
            job->http_body = readFile(req.getError(404));
        } break;
    }

    if (job->http_headers.find("Content-Length:") == std::string::npos &&
        job->http_headers.find("Transfer-Encoding:") == std::string::npos) {
        std::ostringstream oss; oss << job->http_body.size();
        job->http_headers += "Content-Length: " + oss.str() + "\r\n";
    }
    job->http_headers += "Connection: close\r\n";
    std::string full = statusLine + job->http_headers + "\r\n" + job->http_body;
    req.setResponse(job->client_fd, full);
    modifyEpollEvent(epfd, job->client_fd, EPOLLOUT);

    delete job;
}

void CgiReactor::forgetJob(CgiJob* job) {
    if (!job) return;
    if (job->cgi_out >= 0) _byFd.erase(job->cgi_out);
    if (job->cgi_in  >= 0) _byFd.erase(job->cgi_in);
    delete job;
}

void CgiReactor::handleIoEvent(int epfd, int fd, uint32_t events, Request& req) {
    std::map<int, CgiJob*>::iterator it = _byFd.find(fd);
    if (it == _byFd.end()) return;
    CgiJob* job = it->second;

    if (job->cgi_in >= 0 && (events & EPOLLOUT) && fd == job->cgi_in) {
        while (job->in_off < job->in_buf.size()) {
            ssize_t w = write(job->cgi_in, job->in_buf.data() + job->in_off,
                              job->in_buf.size() - job->in_off);
            if (w > 0) job->in_off += (size_t)w;
            else if (w < 0) break;
            else {
                delEpollEvent(epfd, job->cgi_in);
                close(job->cgi_in);
                _byFd.erase(job->cgi_in);
                job->cgi_in = -1;
                break;
            }
        }
        if (job->in_off == job->in_buf.size()) {
            delEpollEvent(epfd, job->cgi_in);
            close(job->cgi_in);
            _byFd.erase(job->cgi_in);
            job->cgi_in = -1;
        }
    }
    if ((fd == job->cgi_out) && (events & (EPOLLIN | EPOLLHUP | EPOLLERR)))  {
        char buf[8192];
        for (;;) {
            ssize_t r = read(job->cgi_out, buf, sizeof(buf));
            if (r > 0) job->out_buf.append(buf, (size_t)r);
            else if (r == 0) {
                delEpollEvent(epfd, job->cgi_out);
                close(job->cgi_out);
                _byFd.erase(job->cgi_out);
                job->cgi_out = -1;
                break;
            }
            else 
            {
                break;
            }
        }
        if (childIsDone_(job->pid)) job->child_exited = true;
        if (job->cgi_in == -1 && job->child_exited) {
            finalize_(epfd, job, req);
        }
    }
}
