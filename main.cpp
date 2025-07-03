/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:28:25 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/03 14:58:45 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Parser.hpp"

#include "lib/lib.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_EVENTS 4

int	flag = 1;

void	signalHandler( int sigNum )
{
	flag = 0;
	(void)sigNum;
}

std::string get_path(const std::string &req)
{
	std::istringstream ss(req);
	std::string method;
	std::string path;
	std::string version;

	ss >> method >> path >> version;
	if (path == "/")
		path = "/index.html";

	return ("www" + path);
}


std::string get_file_content(const std::string &path)
{
	int fd = open(path.c_str(), O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return "";
	}

	std::string content;
	char buffer[4096];
	ssize_t bytes_read;

	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
		content.append(buffer, bytes_read);

	if (bytes_read == -1)
		perror("read");

	close(fd);
	return content;
}

bool ft_ends_with(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length())
        return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}


std::string getMimeType(const std::string &path) {
    if (ft_ends_with(path , ".html")) return "text/html";
    if (ft_ends_with(path , ".css")) return "text/css";
    if (ft_ends_with(path , ".js")) return "application/javascript";
    if (ft_ends_with(path , ".png")) return "image/png";
    if (ft_ends_with(path , ".jpg") || ft_ends_with(path , ".jpeg")) return "image/jpeg";
    return "text/plain";
}

std::string makeHttpResponse(const std::string &body, const std::string &mime, int status = 200) {
    std::ostringstream response;
    response << "HTTP/1.1 " << status << " " << (status == 200 ? "OK" : "Not Found") << "\r\n"
             << "Content-Type: " << mime << "\r\n"
             << "Content-Length: " << body.size() << "\r\n"
             << "Connection: close\r\n"
             << "\r\n"
             << body;
    return response.str();
}


int main()
{
	try
	{
		Parser test("config/test.conf");
		std::vector<Server> server = test.getServer();
		int  epoll = epoll_create(1);
		addEpollEvent(epoll, server[0].getSocket());		
		addEpollEvent(epoll, server[1].getSocket());
		struct epoll_event events[MAX_EVENTS];
		while (flag)
		{
			signal(SIGINT, signalHandler);
			int mov = epoll_wait(epoll, events, MAX_EVENTS, -1);
			for (int i = 0; i < mov; i++)
			{
				int fd = events[i].data.fd;
				int index = isSocket(fd, server);
				if (index >= 0)
				{
                    sockaddr_in client_addr;
                    socklen_t client_len = sizeof(client_addr);
                    int client_fd = accept(server[index].getSocket(), (sockaddr*)&client_addr, &client_len);
					std::cout << "client fd is " << client_fd << std::endl;
                    if (client_fd == -1) {
						break;
                    }
                	int opt = 1;
					setsockopt(client_fd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(1));
					addEpollEvent(epoll, client_fd);
            	} 
				else
				{
            	    // Handle client socket
            	    char buffer[1024];
            	    ssize_t count = read(fd, buffer, sizeof(buffer));
					std::string msg(buffer, count);
					std::cout << "Received: " << msg;
					std::cout << msg << std::endl;
					
					std::string path = get_path(msg);
					std::string content = get_file_content(path);

					std::string mime = getMimeType(path);
					std::string response = makeHttpResponse(content, mime, content == "<h1>404 Not Found</h1>" ? 404 : 200);

					send(fd, response.c_str(), response.size(), 0);
					close(fd); 
				}
			}
		}
		test.closeFds();
		close(epoll);
	}
	catch(const std::exception& e)
	{
	}
	
}