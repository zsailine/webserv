/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:12:25 by zsailine          #+#    #+#             */
/*   Updated: 2025/08/12 11:58:54 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "../Parser/Run.hpp"

sockaddr_in init_adress(std::string str)
{
	struct addrinfo *result;
	sockaddr_in adress;
	std::string host = str.substr(0, str.find(':'));
	std::string port = str.substr(str.find(':') + 1);
	adress.sin_addr.s_addr = INADDR_NONE;
	if (getaddrinfo(host.c_str(), port.c_str(), NULL, &result) != 0)
	{
		std::cerr << "Error configuring socket for host " << host << " in port " << port <<  std::endl;
		return adress;
	}
	struct sockaddr_in *tmp = (struct sockaddr_in *)result->ai_addr;
	adress.sin_addr.s_addr = tmp->sin_addr.s_addr;
	adress.sin_family = AF_INET;
	adress.sin_port = htons(ft_atoi(port));
	freeaddrinfo(result);
	return adress;
}

static int ft_print(int sock, std::string str, int index)
{
	Run	run;
	
	if (str.size())
	{
		addEpollEvent(run.getEpoll(), STDOUT_FILENO);
		std::cout << str << " " << index << std::endl;
		delEpollEvent(run.getEpoll(), STDOUT_FILENO);
	}
	if (sock != -1)
		close(sock);
	return (0);
}
int Server::socketer(std::string tmp)
{
	int sock;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return (ft_print(-1, "Error Configuring socket for Server", index));
	
	int opt = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0)
		return (ft_print(sock,"Error configuring socket for Server ", index)); 

	sockaddr_in adresse = init_adress(tmp);
	if (adresse.sin_addr.s_addr == INADDR_NONE)
		return (ft_print(sock, "", index)); 
	
	if (bind(sock, (sockaddr *)&adresse, sizeof(adresse)) != 0)
		return (ft_print(sock,"Error binding socket for Server ", index)); 
	
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