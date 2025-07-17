/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:23:21 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/17 12:58:16 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sender.hpp"

void	Sender::getMessage( std::string message, int fd )
{
	Tools		tools;
	Response	response(message);
	
	response.run();
	response.defineStatus();
	if (response.getMethod() == "GET")
		response.http(response.getStatus(), "");
	if (response.getMethod() == "POST")
		this->postResponse(message, response);
	if (response.getMethod() == "DELETE")
		this->deleteResponse();
	tools.printAnswer(response);
	this->sendMessage(fd, response.getResponse());
}

void	Sender::postResponse( string &message, Response &ref )
{
	Post	post(message);

	post.parseRequest();
	post.checkError(ref, ref.getStatus());
}

void	Sender::deleteResponse()
{
}

void	Sender::sendMessage( int fd, string message )
{
	size_t	size;

	size = message.size();
	send(fd, message.c_str(), size, 0);
}
