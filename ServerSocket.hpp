/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:10:30 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/16 15:59:08 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERSOCKET_HPP

#define SERVERSOCKET_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/epoll.h>

class ServerSocket
{
	private:
			int _socket;


			sockaddr_in init_adress(int port);
			ServerSocket(){}
			ServerSocket(const ServerSocket &toCopy){(void)toCopy;}
	public:
			ServerSocket(int port);
			~ServerSocket();
			int getSocket() const;
};

#endif