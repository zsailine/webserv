/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 06:12:36 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/01 12:20:08 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "define.hpp"

class Server
{
	private:
	
		int					_socket;
		int					_server;
		struct sockaddr_in	_identity;
	
	public:

		Server();
		~Server();

		int 	getSocket() const;
		int 	getServer() const;

		// init and bind _socket;
		void	startSocket();
		// _socket is waiting for something and accpet first connection
		void	listenSocket();
		// while until there is a connection
		void	whileSocket();
};

#endif
