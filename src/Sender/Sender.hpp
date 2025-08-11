/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:19:34 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/11 09:07:44 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENDER_HPP
#define SENDER_HPP

#include "lib.hpp"
#include "class.hpp"

class Response;

class Sender
{
	private:

		std::string	_response;

	public:

		Sender() {}
		string	handleGet( Server &server, Response &response, Body &body );
		string	handleRequest( int fd, Server &server );
		void	sendMessage( int fd, string message );
		void	postResponse( Body &body );
		// void	deleteResponse( string &message, Response &ref, Server &server );
};

#endif
