/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:12:25 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/30 09:54:14 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

sockaddr_in init_adress(std::string str)
{
	struct addrinfo *result;
	sockaddr_in adress;
	std::string host = str.substr(0, str.find(':'));
	std::string port = str.substr(str.find(':') + 1);
	if (getaddrinfo(host.c_str(), port.c_str(), NULL, &result) != 0)
	{
		std::cerr << "Error Configuring socket for host " << host << " in port " << port <<  std::endl;
		return adress;
	}
	struct sockaddr_in *tmp = (struct sockaddr_in *)result->ai_addr;
	adress.sin_addr.s_addr = tmp->sin_addr.s_addr;
	adress.sin_family = AF_INET;
	adress.sin_port = htons(ft_atoi(port));
	freeaddrinfo(result);
	return adress;
}

int Server::socketer(std::string tmp)
{
	int sock;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cerr << "Error Configuring socket for Server " << index << std::endl; 
		return (0);
	}
	int opt = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0)
			{
				std::cerr << "Error configuring socket for Server " << index << std::endl; 
				return (0);
			}
	sockaddr_in adresse = init_adress(tmp);
	if (bind(sock, (sockaddr *)&adresse, sizeof(adresse)) != 0)
	{
		close (sock);
		std::cerr << "Error binding socket for Server " << index << std::endl; 
		fprintf(stderr, "Message d'erreur : %s\n", strerror(errno)); // Affiche le message d'erreur associé à errno
		return (0);
	}
	if (listen(sock, 2) != 0)
	{
		close (sock);
		std::cerr << "Error listening socket for Server " << index << std::endl; 
		return (0);
	}
	return (sock);
}

int Server::init_socket()
{
	std::string tmp;
	std::stringstream iss(_map["listen"]);
	while (iss >> tmp)
	{
		int fd = socketer(tmp);
		if (!fd)
			return (0);
		_socket.push_back(fd);
	}
	return (1);
}