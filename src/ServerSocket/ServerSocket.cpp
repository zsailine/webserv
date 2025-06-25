/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:53:35 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/24 14:56:23 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#include "ServerSocket.hpp"
#include "../Parser/Server.hpp"
#include "../Utils/utils.cpp"


sockaddr_in ServerSocket::init_adress(Server server)
{
	sockaddr_in adress;
	std::memset(&adress, 0, sizeof(adress));
	adress.sin_family = AF_INET;
	adress.sin_addr = get_resolve_ip(server.getMap()["hostname"]);
	try
	{
		int port = get_port_value(server.getMap()["port"]);
		adress.sin_port = htons(port);
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	return adress;
}

ServerSocket::ServerSocket(Server server)
{
	std::string port;
	sockaddr_in adresse = init_adress(server);

	port = server.getMap()["port"];
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