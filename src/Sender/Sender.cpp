/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:23:21 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/17 15:23:10 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sender.hpp"

void	Sender::handleGet(Server &server, Response &response)
{
	int url = server.check_url(response.getPath());
	if (url == -1)
		return;
	std::string path = server.getValue(url, "root");

	response.set_path(server.getValue(url, "index"), server.getValue(url, "url"),  path);
}

void	Sender::handleRequest( std::string message, int fd, Server &server )
{
	Tools		tools;
	Response	response(message);
	
	response.defineStatus();
	response.set_header(message);
	if (response.getMethod() == "GET")
	{
		this->handleGet(server, response);
		response.run();
		response.http(response.getStatus(), "");
	}
	else if (response.getMethod() == "POST")
		this->postResponse(message, response);
	else if (response.getMethod() == "DELETE")
		this->deleteResponse(response);
	tools.printAnswer(response);
	this->sendMessage(fd, response.getResponse());
}

void	Sender::postResponse( string &message, Response &ref )
{
	Post	post(message);

	post.parseRequest();
	post.checkError(ref, ref.getStatus());
}

void	Sender::deleteResponse( Response &ref )
{
	(void)ref;
}

void	Sender::sendMessage( int fd, string message )
{
	size_t	size;

	size = message.size();
	send(fd, message.c_str(), size, 0);
}
