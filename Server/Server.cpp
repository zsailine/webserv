/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 06:14:22 by mitandri          #+#    #+#             */
/*   Updated: 2025/06/28 18:45:49 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() : _socket() {}

Server::~Server()
{
	close(this->_socket);
}

int	Server::getSocket() const
{
	return this->_socket;
}

int	Server::getServer() const
{
	return this->_server;
}

void	Server::startSocket()
{
	// init a _socket
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket < 0)
		throw(std::invalid_argument(RED "SOCKET ERROR !" RESET));

	// give the socket an identity : init the struct sockaddr_in structure
	this->_identity.sin_port = htons(PORT);
	this->_identity.sin_family = AF_INET;
	this->_identity.sin_addr.s_addr = htons(INADDR_ANY);

	// bind the socket
	if (bind(this->_socket, (struct sockaddr *)&this->_identity, sizeof(this->_identity)) == -1)
		throw(std::invalid_argument(RED "BIND ERROR !" RESET));

	// Log message
	std::cout << "Socket initiated and binded" << std::endl;
	std::cout << "Socket : " << this->_socket << std::endl;
	std::cout << "Adress(port) : " << this->_identity.sin_port << std::endl;
	std::cout << "Adress(family) : " << this->_identity.sin_family << std::endl;
	std::cout << "Adress(addr) : " << this->_identity.sin_addr.s_addr << std::endl;
	std::cout << std::endl;
}

void	Server::listenSocket()
{
	// _socket is listening and waiting from anything
	if (listen(this->_socket, BACKLOG) == -1)
		throw(std::invalid_argument(RED "BIND ERROR !" RESET));
	
	//Log message
	std::cout << "Socket is listening..." << std::endl;
	std::cout << std::endl;
}

void	Server::whileSocket()
{
	string	something("Hello world from server!");

	while (true)
	{
		// _socket is waiting for any first connection
		int	len = sizeof(this->_identity);
		this->_server = accept(this->_socket, (struct sockaddr *)&this->_identity, \
			(socklen_t *)&len);
		if (this->_server == -1)
			throw(std::invalid_argument(RED "ACCEPT ERROR !" RESET));

		// _socket is reading and writing after that
		string	str(BUFFER, 0);
		if (read(this->_server, (char *)str.c_str(), BUFFER) == -1)
			throw(std::invalid_argument(RED "DONE IN SERVER!" RESET));
		std::cout << "Message : " << str << std::endl;
		write(this->_server, something.c_str(), something.size());
		std::cout << std::endl;
		std::cout << "MESSAGE SENT FROM SERVER !" << std::endl;
		close(this->_server);
	}
}
