/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:28:25 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/01 14:16:02 by zsailine         ###   ########.fr       */
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
					std::cout << "tafiditra\n";
            	    ssize_t count = read(fd, buffer, sizeof(buffer));
					std::cout << "fd manao " << fd << " dia count " << count << std::endl;
					std::string msg(buffer, count);
					std::cout << "Received: " << msg;
					std::cout << msg << std::endl;
					send(fd, "HTTP/1.1 200 OK\n", 16, 0);
					send(fd, "Content-length: 49\n", 19, 0);
					send(fd, "Content-Type: text/html\n\n", 25, 0);
					send(fd, "<html><body><input METHOD="POST">Hello webserv</h1></body></html>", 151, 0); //here problems start
				}
				std::cout << "tapitra ho an'ny fd " << fd << std::endl;
			}
		}
		test.closeFds();
		close(epoll);
	}
	catch(const std::exception& e)
	{
	}
	
}