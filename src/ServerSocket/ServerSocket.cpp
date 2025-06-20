/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:53:35 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/20 14:36:30 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerSocket.hpp"

sockaddr_in ServerSocket::init_adress(int port)
{
	sockaddr_in adress;
	adress.sin_addr.s_addr = INADDR_ANY;
	adress.sin_family = AF_INET;
	adress.sin_port = htons(port);
	return adress;
}

ServerSocket::ServerSocket(int port)
{
	sockaddr_in adresse = init_adress(port);
	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cerr << "Error Configuring socket for port " << port << std::endl;
		throw std::exception();
	}
	int opt = 1;
	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt,
		sizeof(opt)) != 0 || setsockopt(_socket, SOL_SOCKET, SO_REUSEPORT, &opt,
		sizeof(opt)) != 0)
	{
			std::cerr << "Error configuring socket for port " << port << std::endl;
			throw std::exception();
	}
	if (bind(_socket, (sockaddr *)&adresse, sizeof(adresse)) != 0)
	{
		std::cerr << "Error binding socket for port " << port << std::endl;
		throw std::exception();
	}
	if (listen(_socket, 2) != 0)
	{
		std::cerr << "Error listening socket for port " << port << std::endl;
		throw std::exception();
	}
}

ServerSocket::~ServerSocket()
{
	close(_socket);	
}

int ServerSocket::getSocket() const
{
	return (_socket);
}