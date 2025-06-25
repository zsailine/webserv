/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:10:30 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/24 14:06:55 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERSOCKET_HPP

#define SERVERSOCKET_HPP

#include "../../lib/lib.hpp"
#include "../Parser/Server.hpp"
#include <cstring>         
#include <netdb.h>
#include <string>
#include <cstring>         // memset
#include <arpa/inet.h>     // inet_ntop
#include <netinet/in.h>    // sockaddr_in
#include <iostream>

class ServerSocket
{
	private:
			int _socket;


			sockaddr_in init_adress(Server server);
			ServerSocket(const ServerSocket &toCopy){(void)toCopy;}
	public:
			ServerSocket(){}
			ServerSocket(Server server);
			~ServerSocket();
			int getSocket() const;
};

#endif