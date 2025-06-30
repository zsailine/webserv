/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:28:25 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/30 15:42:31 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Parser.hpp"

#include "Parser.hpp"

#include <sys/epoll.h>

void addEpollEvent(int epfd, int socket)
{
	struct epoll_event event;

	event.data.fd = socket;
	event.events = EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, socket, &event);
	std::cout << "Socket " << socket << " has been successfully added to epoll.\n";
}

void delEpollEvent(int epfd, int socket)
{
	epoll_ctl(epfd, EPOLL_CTL_DEL, socket, NULL);
	std::cout << "Socket " << socket << " has been successfully deleted to epoll.\n";
}

#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_EVENTS 4

int main()
{
	try
	{
		Parser test("config/test.conf");
		std::vector<Server> server = test.getServer();
		std::cout << "Socket " << server[0].getSocket() << " has been created\n";
		std::cout << "Socket " << server[1].getSocket() << " has been created\n";
		int  epoll = epoll_create(1);
		addEpollEvent(epoll, server[0].getSocket());		
		addEpollEvent(epoll, server[1].getSocket());
		struct epoll_event events[MAX_EVENTS];
		while (1)
		{
			int mov = epoll_wait(epoll, events, MAX_EVENTS, -1);
			std::cout << "mov is " << mov << std::endl;

			for (int i = 0; i < mov; i++)
			{
				int fd = events[i].data.fd;
				if (fd == server[1].getSocket())
				{
                    sockaddr_in client_addr;
                    socklen_t client_len = sizeof(client_addr);
                    int client_fd = accept4(server[1].getSocket(), (sockaddr*)&client_addr, &client_len, SOCK_NONBLOCK);
					std::cout << "client fd is " << client_fd << std::endl;
                    if (client_fd == -1) {
						break;
                    }
                    char ip_str[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, sizeof(ip_str));
                    std::cout << "Accepted connection from " << ip_str << ":" << ntohs(client_addr.sin_port) << "\n";
                   int opt = 1;
					setsockopt(client_fd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(1));
					addEpollEvent(epoll, client_fd);
            	} 
				if (fd == server[0].getSocket())
				{
                    sockaddr_in client_addr;
                    socklen_t client_len = sizeof(client_addr);
                    int client_fd = accept4(server[0].getSocket(), (sockaddr*)&client_addr, &client_len, SOCK_NONBLOCK);
					std::cout << "client fd is " << client_fd << std::endl;
                    if (client_fd == -1) {
						break;
                    }
                    char ip_str[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, sizeof(ip_str));
                    std::cout << "Accepted connection from " << ip_str << ":" << ntohs(client_addr.sin_port) << "\n";
                   int opt = 1;
					setsockopt(client_fd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(1));
					addEpollEvent(epoll, client_fd);
            } 
			else if (events[i].events & EPOLLIN)
			{
                // Handle client socket
				std::cout << "tafiditra\n";
                char buffer[1024];
                ssize_t count = read(fd, buffer, sizeof(buffer));
				std::string msg(buffer, count);
				std::cout << "Received: " << msg;
				std::cout << msg << std::endl;
				send(fd, "HTTP/1.1 200 OK\n", 16, 0);
				send(fd, "Content-length: 49\n", 19, 0);
				send(fd, "Content-Type: text/html\n\n", 25, 0);
				send(fd, "<html><body><h1>Hello webserv</h1></body></html>", 151, 0); //here problems start
				close (fd);
			}
		}
	}
}
	catch(const std::exception& e)
	{
	}
	
}