/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:23:21 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/27 15:39:48 by zsailine         ###   ########.fr       */
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
		response.set_path(server.getError(405));
		response.set_status(405);
		return (-1);
	}
	return (url);
}

void	Sender::handleGet( Server &server, Response &response, Body &body )
{
	response.set_path(body.getPath());
	int url = ft_error_before(server, response);
	if (url == -1)
	{
		response.getExtension();
		body.setContent(readFile(response.getPath()));
		response.http(body);
		return;
	}
	std::string redirection = server.getValue(url, "redirection");
	std::string listing = server.getValue(url, "listingDirectory");
	if (listing.compare("no") && isDirectory(response.getPath()))
	{
		std::string request = response.getPath();
		std::string path = server.getValue(url, "root");
		response.set_path(server.getValue(url, "index"), server.getValue(url, "url"),  path, 1);
		response.makeListing(request, body, server);
		response.http(body);
		return ;
	}
	if (server.getValue(url, "redirection").size() == 0)
	{
		std::string path = server.getValue(url, "root");
		response.set_path(server.getValue(url, "index"), server.getValue(url, "url"),  path, 0);
		ft_Error(server, response);
		response.getExtension();
		body.setContent(readFile(response.getPath()));
		response.http(body);
		return ;
	}
	response.makeRedirection(redirection);
}

int	postStatus( Response &response, Body &body)
{
	Post	post;
	string	type = getType(body.getHeader(), "Content-Type:", "\r\n");

	if (body.getBody().size() == 0)
		return 204;
	if (type.find("boundary") != string::npos)
		type = getType(body.getHeader(), "Content-Type:", ";");
	if (type == "multipart/form-data")
		return post.multipartForm(body.getBody(), body.getBoundary(), response.getPath(), body.getHost());
	else
		return post.uploadFile(body.getBody(), response.getPath(), body.getPath());
	return 501;
}

int	handlePost( Response &response, Body &body, Server &server )
{
	int	status = 201;
	int	url = server.check_url(body.getPath());
	
	if (url == -1)
		return 404;
	if (server.getValue(url, "allowedMethods").find("POST") == string::npos)
		return 405;
	string	path = server.getValue(url, "upload_directory");
	if (not ft_ends_with(path, "/"))
		path.push_back('/');
	response.set_path(path);
	status = postStatus(response, body);
	return status;
}

void	Sender::postResponse( Response &response, Body &body, Server &server )
{
	response.set_path(body.getPath());
	int url = handlePost(response, body, server);
	
	response.set_status(url);
	response.set_mime("text/html");
	if (url < 400)
		response.set_body(generateHTML(response.getStatus(), response.description(response.getStatus())));
	else if (url >= 400)
		response.set_body(readFile(server.getError(url)));
	response.generateHeader(body);
	if (url < 400)
		response.pushNewHeader("Connection: keep-alive");
	if (url == 405)
	{
		int		index = server.check_url(body.getPath());
		if (index == -1)
			response.set_status(500);
		else
		{
			string	allowed = server.getValue(index, "allowedMethods");
			response.pushNewHeader("Allow : " + allowed);
		}
	}
	response.response();
}

static int	deleteStatus( Body &body, Server &server )
{
	size_t	index = body.getPath().rfind('/');
	string	file, url, directory;

	if (index == string::npos) return 400;
	file = body.getPath().substr(index + 1, string::npos);
	if (file == "") return 400;
	url = body.getPath().substr(0, index);
	if (url.size() == 0) url += "/";
	int i = server.check_url(url);
	if (i == -1) return 404;
	directory = server.getValue(i, "upload_directory") + "/";
	if (server.getValue(i, "allowedMethods").find("DELETE") == string::npos)
		return 405;
	file = directory + file;
	if (not fileExist(file)) return 404;
	if (not hasPermission(file, W_OK)) return 403;
	if (std::remove(file.c_str()) == 0)
		return 200;
	else
		return 403;
	return 200;
}

void	Sender::deleteResponse( Response &response, Body &body, Server &server )
{
	int	status;
	
	status = deleteStatus(body, server);
	response.set_status(status);
	response.set_mime("text/html");
	if (status < 400)
		response.set_body(generateHTML(response.getStatus(), response.description(response.getStatus())));
	else if (status >= 400)
		response.set_body(readFile(server.getError(status)));
	response.generateHeader(body);
	if (status < 400)
		response.pushNewHeader("Connection: keep-alive");
	if (status == 405)
	{
		int		index = server.check_url(body.getPath());
		if (index == -1)
			response.set_status(500);
		else
		{
			string	allowed = server.getValue(index, "allowedMethods");
			response.pushNewHeader("Allow : " + allowed);
		}
	}
	response.response();
}
