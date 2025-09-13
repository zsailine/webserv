#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <algorithm>

struct Client {
    int fd;
    std::ifstream file;
    std::vector<char> write_buf;
    size_t write_offset;
    bool header_sent;
    size_t file_size;
    size_t file_bytes_sent;
};

static std::string get_mime(const std::string& path) {
    auto pos = path.find_last_of('.');
    if (pos == std::string::npos) return "application/octet-stream";
    std::string ext = path.substr(pos + 1);
    // to lower
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    if (ext == "html" || ext == "htm") return "text/html";
    if (ext == "css") return "text/css";
    if (ext == "js") return "application/javascript";
    if (ext == "json") return "application/json";
    if (ext == "png") return "image/png";
    if (ext == "jpg" || ext == "jpeg") return "image/jpeg";
    if (ext == "gif") return "image/gif";
    if (ext == "mp4") return "video/mp4";
    if (ext == "webm") return "video/webm";
    if (ext == "svg") return "image/svg+xml";
    return "application/octet-stream";
}

static size_t get_file_size(std::ifstream &f) {
    f.seekg(0, std::ios::end);
    std::streampos end = f.tellg();
    f.seekg(0, std::ios::beg);
    if (end == -1) return 0;
    return static_cast<size_t>(end);
}

int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) { perror("socket"); return 1; }

    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_fd, (sockaddr*)&addr, sizeof(addr)) == -1) { perror("bind"); return 1; }
    if (listen(listen_fd, SOMAXCONN) == -1) { perror("listen"); return 1; }

    if (set_nonblocking(listen_fd) == -1) { perror("fcntl"); /* non-fatal */ }

    int epfd = epoll_create1(0);
    if (epfd == -1) { perror("epoll_create1"); return 1; }

    epoll_event ev{};
    ev.events = EPOLLIN;
    ev.data.fd = listen_fd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &ev) == -1) { perror("epoll_ctl"); return 1; }

    std::map<int, Client*> clients;

    while (true) {
        epoll_event events[64];
        int n = epoll_wait(epfd, events, 64, -1);
        if (n == -1) { if (errno == EINTR) continue; perror("epoll_wait"); break; }

        for (int i = 0; i < n; i++) {
            int fd = events[i].data.fd;

            // handle errors/hangups
            if (events[i].events & (EPOLLHUP | EPOLLERR)) {
                if (fd == listen_fd) continue;
                auto it = clients.find(fd);
                if (it != clients.end()) {
                    close(fd);
                    delete it->second;
                    clients.erase(it);
                } else {
                    close(fd);
                }
                continue;
            }

            if (fd == listen_fd) {
                sockaddr_in client_addr{};
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(listen_fd, (sockaddr*)&client_addr, &client_len);
                if (client_fd == -1) { perror("accept"); continue; }

                if (set_nonblocking(client_fd) == -1) { perror("fcntl(client)"); /* continue anyway */ }

                ev.events = EPOLLIN | EPOLLET; // edge-triggered for clients (optional)
                ev.data.fd = client_fd;
                if (epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
                    perror("epoll_ctl add client");
                    close(client_fd);
                }
            }
            else if (events[i].events & EPOLLIN) {
                char buf[4096];
                int r = read(fd, buf, sizeof(buf)-1);
                if (r <= 0) {
                    // client closed or error
                    close(fd);
                    auto it = clients.find(fd);
                    if (it != clients.end()) { delete it->second; clients.erase(it); }
                    continue;
                }

                buf[r] = '\0';
                std::string req(buf);

                // Simple parse: "GET /path HTTP/1.1"
                if (req.rfind("GET ", 0) == 0) {
                    size_t start = req.find(' ') + 1;
                    size_t end   = req.find(' ', start);
                    std::string uri = (start != std::string::npos && end != std::string::npos) ?
                                        req.substr(start, end - start) : "/";

                    // sanitize: remove leading '/'
                    if (!uri.empty() && uri[0] == '/') uri.erase(0, 1);
                    if (uri.empty()) uri = "index.html";

                    std::ifstream file(uri.c_str(), std::ios::binary);
                    if (!file.is_open()) {
                        const char* notfound =
                            "HTTP/1.1 404 Not Found\r\n"
                            "Content-Length: 13\r\n"
                            "Content-Type: text/plain\r\n"
                            "Connection: close\r\n"
                            "\r\n"
                            "404 Not Found";
                        write(fd, notfound, strlen(notfound));
                        close(fd);
                        continue;
                    }

                    size_t fsize = get_file_size(file);
                    std::string mime = get_mime(uri);

                    Client* client = new Client();
                    client->fd = fd;
                    client->file.swap(file);
                    client->write_offset = 0;
                    client->header_sent = false;
                    client->file_size = fsize;
                    client->file_bytes_sent = 0;

                    // build header now so we know Content-Length
                    std::string header;
                    header += "HTTP/1.1 200 OK\r\n";
                    header += "Content-Type: " + mime + "\r\n";
                    header += "Content-Length: " + std::to_string(client->file_size) + "\r\n";
                    header += "Connection: close\r\n";
                    header += "\r\n";

                    client->write_buf.assign(header.begin(), header.end());
                    client->write_offset = 0;
                    client->header_sent = true; // header already queued in write_buf

                    clients[fd] = client;

                    // switch to EPOLLOUT to start sending header+body
                    ev.events = EPOLLOUT;
                    ev.data.fd = fd;
                    if (epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1) {
                        perror("epoll_ctl mod to out");
                    }
                } else {
                    // not a GET - respond 400
                    const char* bad =
                        "HTTP/1.1 400 Bad Request\r\n"
                        "Content-Length: 11\r\n"
                        "Content-Type: text/plain\r\n"
                        "Connection: close\r\n"
                        "\r\n"
                        "Bad Request";
                    write(fd, bad, strlen(bad));
                    close(fd);
                }
            }
            else if (events[i].events & EPOLLOUT) {
                Client* client = nullptr;
                auto it = clients.find(fd);
                if (it != clients.end()) client = it->second;
                if (!client) continue;

                // If there is a pending write_buf (header or a previously read block), write it first.
                std::cout << "tafidtra for " << client->write_buf.data() << std::endl;
                while (client->write_offset < client->write_buf.size()) {
                    ssize_t w = write(fd,
                                      client->write_buf.data() + client->write_offset,
                                      client->write_buf.size() - client->write_offset);
                    if (w == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) break;
                        close(fd);
                        delete client;
                        clients.erase(fd);
                        goto next_event;
                    }
                    client->write_offset += static_cast<size_t>(w);
                }
                
                // Ici, on supprime write_buf seulement si tout est écrit
                if (client->write_offset >= client->write_buf.size()) {
                    client->write_buf.clear();
                    client->write_offset = 0;
                }

                    if (client->file && client->file_bytes_sent < client->file_size) {
                        char block[4096];
                        size_t want = std::min(sizeof(block), client->file_size - client->file_bytes_sent);
                        std::streamsize got =client->file.rdbuf()->sgetn(block, sizeof(block));
                        // client->file.read(block, want);
                        // std::streamsize got = client->file.gcount();
                        if (got > 0) {
                            client->write_buf.assign(block, block + got);
                            client->file_bytes_sent += static_cast<size_t>(got);
                            client->write_offset = 0;
                            std::cerr <<"Got " << got <<" Buffered " << client->write_buf.size()
                 << " bytes, total sent=" << client->file_bytes_sent << "\n";
                        } else {
                            // no more data
                            client->file.close();
                        }
                    }

                // If we've sent everything (no pending write_buf and no file data), close
                if (client->write_buf.empty() && (!client->file || client->file_bytes_sent >= client->file_size)) {
                    close(fd);
                    delete client;
                    clients.erase(fd);
                }

                next_event: ;
            }
        }
    }

    close(listen_fd);
    return 0;
}
