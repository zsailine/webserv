/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:02:47 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/12 11:24:16 by mitandri         ###   ########.fr       */
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
		corpse = body.substr(size + 4, bLength);
		string	boundary = getType(header, "boundary=", "\r\n");
		bod.setLength(bLength);
		bod.setBoundary("--" + boundary);
		bod.setBody(corpse);
	}
	bod.setHost(getType(header, "Host:", "\r\n"));
	std::istringstream iss(header);
	bod.setFirst(iss);
	return this->handleRequest(fd, bod, server);
}

bool	Request::handleRequest( int fd, Body &bod, Server &server )
{
	Sender			sender;
	Response		response;
	string			beforebefore;
	static string	before = "";

	response.defineStatus();
	if (bod.getMethod() == "GET")
	{
		beforebefore = sender.handleGet(server, response, bod);
		response.getExtension();
		bod.setContent(readFile(response.getPath()));
		response.http(bod, "");
	}
	else if (bod.getMethod() == "POST")
		sender.postResponse(response, bod, server);
	else if (bod.getMethod() == "DELETE")
		sender.deleteResponse(server.get("listen"), response, bod);
	else
		throw(std::invalid_argument(RED "METHOD ERROR\t:\t" + bod.getMethod() + " NOT SUPPORTED" RESET));
	printLogs(bod.getMethod(), bod.getPath(), bod.getVersion());
	this->_response[fd] = response.getResponse();
	before = beforebefore;
	return true;
}

bool	Request::sendChunks( int fd )
{
	size_t sent = send(fd, this->_response[fd].c_str(), this->_response[fd].size(), 0);
	if (sent != this->_response[fd].size())
		return false;
	this->_req[fd].clear();
	this->_body[fd].clear();
	this->_header[fd].clear();
	this->_response[fd].clear();
	return true;
}

Request::Request() {}
Request::~Request() {}
