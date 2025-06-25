/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:27:30 by aranaivo          #+#    #+#             */
/*   Updated: 2025/06/24 14:57:40 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <string>
#include <algorithm>
#include <cctype> // Pour std::isspace
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>


#include "lib/lib.hpp"
#include "src/Parser/Server.hpp"
#include "src/ServerSocket/ServerSocket.hpp"

#define PORT 8080
#define BUF_SIZE 4096
#define MAX_EVENTS 2


int main(void)
{
	std::vector<Server> servers;

	std::vector<std::string> block1;
	block1.push_back("host = localhost");
	block1.push_back("port = 8080");
	Server server1(1, block1);

	std::vector<std::string> block2;
	block2.push_back("host = localhost");
	block2.push_back("port = 1654");
	Server server2(2, block2);

	servers.push_back(server1);
	servers.push_back(server2);


	//Initialisation epoll
	int epfd = epoll_create(1);
	if (epfd == -1)
	{
		std::cout << "error has occured on epoll";
		return (1);
	}

	std::vector<int> sockets;

	for (size_t i = 0; i < servers.size(); i++)
	{
		//creation socket
		ServerSocket socket(servers[i]);
		servers[i].create_socket();
		//sockets.push_back(ServerSocket(servers[i]));

		//std::cout << servers[i].getSocket() << std::endl;
		//add sochet to epoll
	}

	//Boucle principal
	//epoll wait
	return (0);
}

// int main()
// {
    
// 	ServerSocket socket1(80);
// 	int epoll = epoll_create(1);
// 	epoll_event events[MAX_EVENTS];
// 	addEpollEvent(epoll, socket1.getSocket());
// 	std::cout << "epoll is " << epoll << std::endl; 
// 	std::cout << "socket is at " << socket1.getSocket() << std::endl;
// 	while (1)
// 	{
// 		int mov = epoll_wait(epoll, events, MAX_EVENTS, -1);
// 		std::cout << "mov is " << mov << std::endl;

// 		for (int i = 0; i < mov; i++)
// 		{
// 			int fd = events[i].data.fd;
// 			if (fd == socket1.getSocket()){
//                     sockaddr_in client_addr;
//                     socklen_t client_len = sizeof(client_addr);
//                     int client_fd = accept4(socket1.getSocket(), (sockaddr*)&client_addr, &client_len, SOCK_NONBLOCK);
// 					std::cout << "client fd is " << client_fd << std::endl;
//                     if (client_fd == -1) {
// 						break;
//                     }
//                     char ip_str[INET_ADDRSTRLEN];
//                     inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, sizeof(ip_str));
//                     std::cout << "Accepted connection from " << ip_str << ":" << ntohs(client_addr.sin_port) << "\n";
//                    int opt = 1;
// 					setsockopt(client_fd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(1));
// 					addEpollEvent(epoll, client_fd);
//             } else if (events[i].events & EPOLLIN){
//                 // Handle client socket
// 				std::cout << "tafiditra\n";
//                 char buffer[1024];
//                 ssize_t count = read(fd, buffer, sizeof(buffer));
// 				std::string msg(buffer, count);
// 				std::cout << "Received: " << msg;
// 				std::cout << msg << std::endl;
// 				send(fd, "HTTP/1.1 200 OK\n", 16, 0);
// 				send(fd, "Content-length: 49\n", 19, 0);
// 				send(fd, "Content-Type: text/html\n\n", 25, 0);
// 				send(fd, "<html><body><h1>Hello webserv</h1></body></html>", 151, 0); //here problems start
// 				close (fd);
// 			}
// 	}
// 	}
// 	delEpollEvent(epoll, socket1.getSocket());            
// 	return (0);
// }
