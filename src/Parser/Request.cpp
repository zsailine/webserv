/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:02:47 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/31 14:35:08 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

void	Request::readChunks( int fd, Server &server )
{
	Tools	tools;
	char	buffer[8192];
	size_t	byte;

	byte = read(fd, buffer, sizeof(buffer));
	if (byte > 0)
	{
		buffer[byte] = 0;
		this->_req[fd].append(buffer, byte);
		if (this->_req[fd].find("\r\n\r\n") != string::npos)
		{
			int		bLength, total;
			string	&body = this->_req[fd];
			(body.find("Content-Length:") != string::npos) ?
				bLength = ft_atoi(tools.getType(body, "Content-Length:", "\r\n"))
				: bLength = 0;
			total = body.find("\r\n\r\n") + 4 + bLength;
			if ((int)body.size() >= total)
			{
				parseRequest(fd, body, bLength, server);
				body.clear();
			}
		}
	}
}

void	Request::parseRequest( int fd, string &body, int bLength, Server &server )
{
	Body	bod;
	Tools	tools;
	string	&header = this->_header[fd];
	size_t	size = body.find("\r\n\r\n");
	
	if (size == string::npos)
		return;
	header = body.substr(0, size);
	if (header.find("Content-Length:") != string::npos)
	{
		string	&corpse = this->_body[fd];
		corpse = body.substr(size + 1, bLength);
		string	boundary = tools.getType(header, "boundary=", "\r\n");
		bod.setLength(bLength);
		bod.setBoundary(boundary);
	}
	std::istringstream iss(header);
	bod.setFirst(iss);
	tools.printLogs(bod.getMethod(), bod.getPath(), bod.getVersion());
	this->handleRequest(fd, bod, server);
}

void	Request::handleRequest( int fd, Body &bod, Server &server )
{
	Sender			sender;
	Response		response;
	string			beforebefore;
	static string	before;

	response.defineStatus();
	if (bod.getMethod() == "GET")
	{
		beforebefore = sender.handleGet(server, response, bod);
		response.getExtension();
		std::cout << RED << response.getPath() << RESET << std::endl;
		bod.readFile(response.getPath());
		response.http(bod, "");
	}
	std::cout << RED << bod.getContent() << RESET << std::endl;
	sender.sendMessage(fd, response.getResponse());
	before = beforebefore;
}

Request::Request()
	: _header(), _body(), _req() {}
Request::~Request() {}
