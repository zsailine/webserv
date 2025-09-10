#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string.h>
#include <errno.h>

struct Client {
    int fd;
    std::ifstream file;
    std::vector<char> write_buf;
    size_t write_offset;
    bool header_sent;
};

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

            if (fd == listen_fd) {
                sockaddr_in client_addr{};
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(listen_fd, (sockaddr*)&client_addr, &client_len);
                if (client_fd == -1) { perror("accept"); continue; }

                ev.events = EPOLLIN;
                ev.data.fd = client_fd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);
            }
            else if (events[i].events & EPOLLIN) {
                char buf[1024];
                int r = read(fd, buf, sizeof(buf)-1);
                if (r <= 0) { close(fd); continue; }

                buf[r] = '\0';
                std::string req(buf);

                if (req.find("GET") == 0) {
                    const char* filename = "get/video1.mp4";
                    std::ifstream file(filename, std::ios::binary);
                    if (!file.is_open()) {
                        const char* notfound =
                            "HTTP/1.1 404 Not Found\r\n"
                            "Content-Length: 13\r\n"
                            "Content-Type: text/plain\r\n"
                            "\r\n"
                            "404 Not Found";
                        write(fd, notfound, strlen(notfound));
                        close(fd);
                        continue;
                    }

                    Client* client = new Client();
                    client->fd = fd;
                    client->file.swap(file);
                    client->write_offset = 0;
                    client->header_sent = false;

                    clients[fd] = client;

                    ev.events = EPOLLOUT;
                    ev.data.fd = fd;
                    epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
                }
            }
            else if (events[i].events & EPOLLOUT) {
                Client* client = clients[fd];
                if (!client) continue;

                if (!client->header_sent) {
                    std::string header =
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Type: video/mp4\r\n"
                        "\r\n";
                    client->write_buf.assign(header.begin(), header.end());
                    client->write_offset = 0;
                    client->header_sent = true;
                }

                if (client->write_offset >= client->write_buf.size() && client->file) {
                    char block[4096];
                    client->file.read(block, sizeof(block));
                    std::streamsize n = client->file.gcount();
                    if (n > 0) {
                        client->write_buf.assign(block, block + n);
                        client->write_offset = 0;
                    } else {
                        client->file.close();
                    }
                }

                while (client->write_offset < client->write_buf.size()) {
                    int w = write(fd, client->write_buf.data() + client->write_offset,
                                  client->write_buf.size() - client->write_offset);
                    if (w == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) break;
                        close(fd);
                        delete client;
                        clients.erase(fd);
                        goto next;
                    }
                    client->write_offset += w;
                }

                if (client->write_offset >= client->write_buf.size() && !client->file) {
                    close(fd);
                    delete client;
                    clients.erase(fd);
                }

                next: ;
            }
        }
    }

    close(listen_fd);
    return 0;
}
