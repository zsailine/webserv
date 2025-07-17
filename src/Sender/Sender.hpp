/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:19:34 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/17 15:20:17 by mitandri         ###   ########.fr       */
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

		void	handleGet(Server &server, Response &response);
		
	public:

		Sender() {}
		void	handleRequest( std::string message, int fd, Server &server );
		void	sendMessage( int fd, string message );
		void	postResponse( string &message, Response &ref );
		void	deleteResponse( Response &ref );
};

#endif
