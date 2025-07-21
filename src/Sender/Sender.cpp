/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:23:21 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/21 10:12:03 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sender.hpp"

void	Sender::handleGet(Server &server, Response &response)
{
	// int				status = 200;
	int url = server.check_url(response.getPath());
	if (url == -1)
		return;
	std::string path = server.getValue(url, "root");

	response.set_path(server.getValue(url, "index"), server.getValue(url, "url"),  path);
	// response.get_file_content();
	// response.get_mime_type();
	// if (open(response.get_path().c_str(), O_RDONLY) < 0)
	// 	status = 404;
	// response.make_Http_response(status);
	// send(fd, response.get_response().c_str(), response.get_response().size(), 0);
}

void	Sender::handleRequest( std::string message, int fd, Server &server )
{
	Tools		tools;
	Response	response(message);
	
	response.defineStatus();
	response.set_header(message);

	std::cout << "******************\n"; 
	std::cout << "path :" << response.getPath() << std::endl;
	std::cout << "method : " << response.getMethod() << std::endl;

	std::cout << "******************\n";

	

	if (response.getMethod() == "GET")
	{
		this->handleGet(server, response);
		response.run();
		response.http(response.getStatus(), "");
	}
	if (response.getMethod() == "POST")
		this->postResponse(message, response);
	if (response.getMethod() == "DELETE")
		this->deleteResponse();
	//tools.printAnswer(response);
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
