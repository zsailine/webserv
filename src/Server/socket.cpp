/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:12:25 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/01 10:22:24 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static int	check_port(std::string &port)
{
	std::stringstream str(port);
	int nbr;

	str >> nbr;
	if (nbr > 65535)
	{
		std::cerr << "Error: port can't be superior to 65535\n";
		throw std::exception();
	}
	return (nbr);
}

sockaddr_in Server::init_adress()
{
	sockaddr_in adress;
	struct addrinfo *result;
	if (getaddrinfo(_map["host"].c_str(), NULL, NULL, &result) != 0)
	{
		std::cerr << "Error Configuring socket for host" << _map["host"] << " in port " << _map["port"] << std::endl;
		throw std::exception();
	}
	struct sockaddr_in *tmp = (struct sockaddr_in *)result->ai_addr;
	adress.sin_addr.s_addr = tmp->sin_addr.s_addr;
	adress.sin_family = AF_INET;
	adress.sin_port = htons(check_port(_map["port"]));
	freeaddrinfo(result);
	return adress;
}

void Server::init_socket()
{
	sockaddr_in adresse = init_adress();
	std::string port = _map["port"] ;
	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cerr << "Error Configuring socket for host" << _map["host"] << " in port " << port << std::endl;
		throw std::exception();
	}
	int opt = 1;
	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt,
		sizeof(opt)) != 0 || setsockopt(_socket, SOL_SOCKET, SO_REUSEPORT, &opt,
		sizeof(opt)) != 0)
	{
			std::cerr << "Error configuring socket for host" << _map["host"] << " in port " << port << std::endl;
			throw std::exception();
	}
	if (bind(_socket, (sockaddr *)&adresse, sizeof(adresse)) != 0)
	{
		std::cerr << "Error binding socket for host" << _map["host"] << " in port " << port << std::endl;
		throw std::exception();
	}
	if (listen(_socket, 2) != 0)
	{
		std::cerr << "Error listening socket for host" << _map["host"] << " in port " << port << std::endl;
		throw std::exception();
	}
}