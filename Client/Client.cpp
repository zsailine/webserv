/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:47:42 by mitandri          #+#    #+#             */
/*   Updated: 2025/06/28 18:48:03 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _socket(0) {}

Client::~Client()
{
	close(this->_socket);
}

int	Client::getSocket() const
{
	return this->_socket;
}

void	Client::startSocket()
{
	string	something("Hello from client !");
	
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket == -1)
		throw(std::invalid_argument(RED "SOCKET ERROR !" RESET));
	this->_identity.sin_family = AF_INET;
	this->_identity.sin_port = htons(PORT);
	if (inet_pton(AF_INET, "127.0.0.1", &this->_identity.sin_addr) <= 0)
		throw(std::invalid_argument(RED "INVALID ADRESS ERROR !" RESET));
	if (connect(this->_socket, (struct sockaddr *)&this->_identity, sizeof(this->_identity)) < 0)
		throw(std::invalid_argument(RED "CONNECTION FAILED !" RESET));
	send(this->_socket, something.c_str(), something.size(), 0);
	std::cout << std::endl;
	std::cout << "MESSAGE SENT FROM CLIENT !" << std::endl;
	string	str(1024, 0);
	if (read(this->_socket, (char *)str.c_str(), 1024) == -1)
		throw(std::invalid_argument(RED "DONE IN CLIENT!" RESET));
	std::cout << str << std::endl;
}
