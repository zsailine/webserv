/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:34:41 by zsailine          #+#    #+#             */
/*   Updated: 2025/08/26 15:54:46 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"
#include "CgiReactor.hpp"
#include "CgiJob.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <cctype>

static int make_pipe_nonblock(int p[2])
{
    if (pipe(p) == -1) return -1;
    int fl;

    fl = fcntl(p[0], F_GETFL, 0);
    if (fl != -1) fcntl(p[0], F_SETFL, fl | O_NONBLOCK);
    fl = fcntl(p[1], F_GETFL, 0);
    if (fl != -1) fcntl(p[1], F_SETFL, fl | O_NONBLOCK);

    fl = fcntl(p[0], F_GETFD);
    if (fl != -1) fcntl(p[0], F_SETFD, fl | FD_CLOEXEC);
    fl = fcntl(p[1], F_GETFD);
    if (fl != -1) fcntl(p[1], F_SETFD, fl | FD_CLOEXEC);

    return 0;
}

static void free_envp_(char** envp) {
    if (!envp) return;
    size_t i = 0;
    while (envp[i]) { delete [] envp[i]; ++i; }
    delete [] envp;
}

void CGI::retrieve_query_string() {
    _query_string.clear();
    std::string::size_type q = _request_uri.find('?');
    if (q != std::string::npos && q + 1 < _request_uri.size()) {
        _query_string = _request_uri.substr(q + 1);
    }
}

static std::string toUpperUnderscore(const std::string& in)
{
    std::string out;
    for (std::string::size_type i = 0; i < in.size(); ++i) {
        char c = in[i];
        if (c == '-') out += '_';
        else out += (char)std::toupper((unsigned char)c);
    }
    return out;
}

char** CGI::generate_envp()
{
    std::vector<std::string> env;

    env.push_back("GATEWAY_INTERFACE=CGI/1.1");
    env.push_back("SERVER_PROTOCOL=HTTP/1.1");
    env.push_back("SERVER_SOFTWARE=MyWebServer/0.1");
    env.push_back("REQUEST_METHOD=" + _method);

    if (!_script_name.empty()) env.push_back("SCRIPT_NAME=" + _script_name);
    if (!_script_path.empty()) env.push_back("SCRIPT_FILENAME=" + _script_path);
    if (!_request_uri.empty()) env.push_back("REQUEST_URI=" + _request_uri);

    env.push_back("QUERY_STRING=" + _query_string);

    if (!_document_root.empty()) env.push_back("DOCUMENT_ROOT=" + _document_root);
    if (!_server_name.empty())   env.push_back("SERVER_NAME=" + _server_name);
    if (!_server_port.empty())   env.push_back("SERVER_PORT=" + _server_port);
    if (!_remote_addr.empty())   env.push_back("REMOTE_ADDR=" + _remote_addr);
    if (!_remote_port.empty())   env.push_back("REMOTE_PORT=" + _remote_port);
    
    if (_method == "POST") {
        std::ostringstream oss; 
        oss << _body.size();
        env.push_back("CONTENT_LENGTH=" + oss.str());
        std::map<std::string,std::string>::const_iterator itCT = _headers.find("Content-Type");
        if (itCT != _headers.end() && !itCT->second.empty()) {
            env.push_back("CONTENT_TYPE=" + itCT->second);
        } else {
            env.push_back("CONTENT_TYPE=application/x-www-form-urlencoded");
        }
    }
    // HEADERS → HTTP_*
    for (std::map<std::string,std::string>::const_iterator it = _headers.begin();
         it != _headers.end(); ++it) {
        const std::string& name = it->first;
        const std::string& value = it->second;
        if (name.empty() || value.empty()) continue;
        if (name == "Content-Type" || name == "Content-Length") continue;
        std::string key = "HTTP_" + toUpperUnderscore(name);
        env.push_back(key + "=" + value);
    }
    env.push_back("REDIRECT_STATUS=200");
    char** envp = new char*[env.size() + 1];
    for (size_t i = 0; i < env.size(); ++i) {
        envp[i] = new char[env[i].size() + 1];
        strcpy(envp[i], env[i].c_str());
    }
    envp[env.size()] = 0;
    return envp;
}


bool CGI::start_cgi(Request &req, int epfd, int client_fd)
{
    int outp[2];
    
    if (make_pipe_nonblock(outp) < 0) 
        return false;
    int inp[2] = { -1, -1 };
    bool isPost = (_method == "POST");
    if (isPost && make_pipe_nonblock(inp) < 0) 
    {
        close(outp[0]); close(outp[1]);
        return false;
    }

    retrieve_query_string();
    char** envp = generate_envp();
    pid_t pid = fork();
    if (pid == -1) {
        if (isPost) { close(inp[0]); close(inp[1]); }
        close(outp[0]); close(outp[1]);
        free_envp_(envp);
        return false;
    }
    if (pid == 0) {
        // enfant
        dup2(outp[1], STDOUT_FILENO);
        if (isPost) 
            dup2(inp[0], STDIN_FILENO);
        close(outp[0]); 
        close(outp[1]);
        close(epfd);
        close(client_fd);
        req.closeSocket();
        if (isPost) 
        { 
            close(inp[0]); 
            close(inp[1]); 
        }
        const char* php_path = "/usr/bin/php-cgi";
        char* argv[2]; argv[0] = (char*)"php-cgi"; argv[1] = 0;
        execve(php_path, argv, envp);
        perror("execve php-cgi failed");
        _exit(127);
    }

    // parent
    close(outp[1]);
    if (isPost) 
        close(inp[0]);
    free_envp_(envp);
    CgiJob* job = new CgiJob();
    job->client_fd = client_fd;
    job->pid       = pid;
    job->cgi_out   = outp[0];
    job->cgi_in    = isPost ? inp[1] : -1;
    if (isPost) 
    {
        job->in_buf = _body;
        job->in_off = 0;
    }
    CgiReactor::instance().registerJob(epfd, job);
    return true;
}


