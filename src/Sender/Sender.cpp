/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:23:21 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/21 15:13:24 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sender.hpp"

static void	ft_Error(Server &server, Response &response)
{
	if (access(response.getPath().c_str(), F_OK) != 0)
	{
		response.set_status(404);
		response.set_path(server.getError(404));
		return ;
	}
	if (response.getPath().find("..") != std::string::npos || access(response.getPath().c_str(), R_OK) != 0)
	{
		response.set_status(403);
		response.set_path(server.getError(403));
		return ;
	}
}

static int ft_error_before(Server &server, Response &response)
{
	int url = server.check_url(response.getPath());
	if (url == -1)
	{
		response.set_path(server.getError(404));
		response.set_status(404);
		return (url);
	}
	if (server.getValue(url, "allowedMethods").find("GET") == std::string::npos)
	{
		response.set_path(server.getError(403));
		response.set_status(403);
		return (-1);
	}
	return (url);
}

std::string	Sender::handleGet(Server &server, Response &response)
{
	int url = ft_error_before(server, response);
	if (url == -1)
		return "";
	std::string path = server.getValue(url, "root");
	response.set_path(server.getValue(url, "index"), server.getValue(url, "url"),  path);
	ft_Error(server, response);
	return (server.getValue(url, "allowedMethods"));
}

std::string	Sender::handleRequest( std::string message, int fd, Server &server, std::string before )
{
	Tools		tools;
	Response	response(message);
	std::string	before2;
	(void)before;
	
	response.defineStatus();
	response.set_header(message);
	if (response.getMethod() == "GET")
	{
		before2 = this->handleGet(server, response);
		response.run();
		response.http(response.getStatus(), "");
	}
	if (response.getMethod() == "POST")
		this->postResponse(message, response);
	if (response.getMethod() == "DELETE")
		this->deleteResponse();
	tools.printAnswer(response);
	this->sendMessage(fd, response.getResponse());
	return (before2);
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
