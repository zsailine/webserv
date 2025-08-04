/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:02:47 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/04 14:23:18 by mitandri         ###   ########.fr       */
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
	if (header.find("Content-Length:") != string::npos)
	{
		string	&corpse = this->_body[fd];
		corpse = body.substr(size + 1, bLength);
		string	boundary = getType(header, "boundary=", "\r\n");
		bod.setLength(bLength);
		bod.setBoundary(boundary);
	}
	std::istringstream iss(header);
	bod.setFirst(iss);
	printLogs(bod.getMethod(), bod.getPath(), bod.getVersion());
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
	this->_response = response.getResponse();
	before = beforebefore;
	return true;
}

bool	Request::sendChunks( int fd )
{
	send(fd,  this->_response.c_str(), this->_response.size(), 0);
	return true;
}

Request::Request()
	: _header(), _body(), _req() {}
Request::~Request() {}
