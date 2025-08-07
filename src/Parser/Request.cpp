/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:02:47 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/07 18:14:24 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

bool	Request::readChunks( int fd, Server &server )
{
	bool	flag = false;
	char	buffer[BUFFER_SIZE];
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
				bLength = ft_atoi(getType(body, "Content-Length:", "\r\n"))
				: bLength = 0;
			total = body.find("\r\n\r\n") + 4 + bLength;
			if ((int)body.size() >= total)
			{
				flag = parseRequest(fd, body, bLength, server);
				body.clear();
			}
		}
	}
	return flag;
}

bool	Request::parseRequest( int fd, string &body, int bLength, Server &server )
{
	Body	bod;
	string	&header = this->_header[fd];
	size_t	size = body.find("\r\n\r\n");
	
	if (size == string::npos)
		return false;
	header = body.substr(0, size);
	bod.setHeader(header);
	if (header.find("Content-Length:") != string::npos)
	{
		string	&corpse = this->_body[fd];
		corpse = body.substr(size + 5, bLength);
		string	boundary = getType(header, "boundary=", "\r\n");
		bod.setLength(bLength);
		bod.setBoundary("--" + boundary);
		bod.setBody(corpse);
	}
	bod.setHost(getType(header, "Host:", "\r\n"));
	std::istringstream iss(header);
	bod.setFirst(iss);
	return this->handleRequest(bod, server);
}

bool	Request::handleRequest( Body &bod, Server &server )
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
		bod.setContent(readFile(response.getPath()));
		response.http(bod, "");
	}
	else if (bod.getMethod() == "POST")
	{
		sender.postResponse(bod);
	}
	else
		throw(std::invalid_argument(RED "METHOD ERROR\t:\t" + bod.getMethod() + " NOT SUPPORTED" RESET));
	printLogs(bod.getMethod(), bod.getPath(), bod.getVersion());
	this->_response = response.getResponse();
	before = beforebefore;
	return true;
}

bool	Request::sendChunks( int fd )
{
	static size_t	sent = 0;
	size_t	rest, chunk, write;

	rest = this->_response.size() - sent;
	(rest > BUFFER_SIZE) ? chunk = BUFFER_SIZE : chunk = rest;
	write = send(fd,  this->_response.c_str() + sent, chunk, 0);
	if (write > 0)
		sent += write;
	if (sent == this->_response.size())
	{
		sent = 0;
		return true;
	}
	return false;
}

Request::Request()
	: _header(), _body(), _req() {}
Request::~Request() {}
