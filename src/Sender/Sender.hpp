/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:19:34 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/25 09:51:25 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENDER_HPP
#define SENDER_HPP

#include "lib.hpp"
#include "class.hpp"

class Response;
class Post;

class Sender
{
	private:

		std::string	_response;

		std::string	handleGet(Server &server, Response &response);
		
	public:

		Sender() {}
		std::string	handleRequest( std::string message, int fd, Server &server, std::string before );
		void		sendMessage( int fd, string message );
		void		postResponse( string &message, Response &ref );
		void		deleteResponse();
};

#endif
