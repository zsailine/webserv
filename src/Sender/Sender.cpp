/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:23:21 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/11 13:12:08 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sender.hpp"
#include "Delete.hpp"

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

string	Sender::handleGet( Server &server, Response &response, Body &body )
{
	response.set_path(body.getPath());
	int url = ft_error_before(server, response);
	if (url == -1)
		return "";
	std::string path = server.getValue(url, "root");
	response.set_path(server.getValue(url, "index"), server.getValue(url, "url"),  path);
	ft_Error(server, response);
	return (server.getValue(url, "allowedMethods"));
}

void	Sender::postResponse( Response &response, Body &body, Server &server )
{
	Post	post;
	string	type = getType(body.getHeader(), "Content-Type:", "\r\n");

	try {
	if (type == "application/x-www-form-urlencoded")
		post.urlEncoded(body.getBody(), server.get("listen"));
	else if (type == "multipart/form-data")
		post.multipartForm(body.getBody(), body.getBoundary(), body.getHeader(), body.getHost());
	else if (type == "text/plain")
		post.textPlain(body.getBody(), body.getHost());
	else if (type == "application/octet-stream")
		writeFile("./upload", body.getBody());
	else
		throw(std::invalid_argument(RED "POST ERROR\t:\t" + type + " not supported" RESET));
	post.checkException(server.get("upload_directory"));
	}
	catch ( const std::exception &e ) {
		if (dynamic_cast<const Post::E200 *>(&e))
			response.set_status(200);
		else if (dynamic_cast<const Post::E201 *>(&e))
			response.set_status(201);
		else if (dynamic_cast<const Post::E204 *>(&e))
			response.set_status(204);
		else if (dynamic_cast<const Post::E400 *>(&e))
			response.set_status(400);
		else if (dynamic_cast<const Post::E403 *>(&e))
			response.set_status(403);
		else if (dynamic_cast<const Post::E404 *>(&e))
			response.set_status(404);
		response.http(body, generateHTML(response.getStatus(), response.description(response.getStatus())));
	}
}

void	Sender::deleteResponse( string host, Response &response, Body &body )
{
	Delete	del;

	del.deleteResource(host, body.getHeader());
	response.http(body, generateHTML(200, response.description(200)));
}

