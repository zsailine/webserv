/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:28:25 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/04 15:18:33 by aranaivo         ###   ########.fr       */
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
            	    ssize_t count = read(fd, buffer, sizeof(buffer));
					std::string msg(buffer, count);
					std::cout << "****************\n";
					std::cout << "Received: " << msg << std::endl;
					std::cout << "****************\n";
					//std::cout << msg << std::endl;
					
					ServerResponse response(msg);
					response.get_full_path(msg);
					response.get_file_content();
					response.get_mime_type();
					int status = 200;
					if (open(response.get_path().c_str(), O_RDONLY) < 0)
						status = 400;
					response.make_Http_response(status);
					send(fd, response.get_response().c_str(), response.get_response().size(), 0);
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