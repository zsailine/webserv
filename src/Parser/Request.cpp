/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:02:47 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/26 09:36:31 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

bool	Request::readChunks( int &fd, Server &server )
{
	bool	flag = false;
	char	buffer[BUFFER_SIZE];
	int		byte;

	byte = read(fd, buffer, sizeof(buffer));
	if (byte == 0 || byte == -1)
	{
		server.setfd(fd, -1);
		close(fd);
	}
	else if (byte > 0)
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

static int	checkHeader( string &header, Body &body, Server &server )
{
	if (header.size() > BUFFER_SIZE)
		return 431;
	if (body.getMethod() != "GET" && body.getMethod() != "POST" && body.getMethod() != "DELETE")
		return 405;
	if (body.getVersion() != "HTTP/1.1")
		return 505;
	string	host = getType(header, "Host:", "\r\n");
	size_t	index = host.find(':');
	if (index == string::npos)
		return 400;
	if (host.substr(0, index) != server.get("server_name"))
		return 400;
	string	listen = server.get("listen");
	if (host.c_str() + (index + 1) != listen.substr(listen.find(':') + 1, string::npos))
		return 400;
	return true;
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
	std::istringstream iss(header);
	bod.setFirst(iss);
	int	headValue = checkHeader(header, bod, server);
	if (headValue != 1)
	{
		Response	rep;
		printLogs(bod.getMethod(), bod.getPath(), bod.getVersion());
		rep.set_status(headValue);
		rep.set_mime("text/html");
		if (bod.getMethod() != "HEAD")
			rep.set_body(readFile(server.getError(headValue)));
		rep.generateHeader(bod);
		if (headValue == 405)
			rep.pushNewHeader("Allow: GET, POST, DELETE");
		if (headValue >= 400)
			rep.pushNewHeader("Connection: close");
		rep.response();
		printAnswer(bod, rep);
		this->_response[fd] = rep.getResponse();
		throw std::invalid_argument("TOO LARGE");
	}
	if (header.find("Content-Length:") != string::npos)
	{
		string	&corpse = this->_body[fd];
		corpse = body.substr(size + 4, bLength);
		long	max = ft_atoi(server.get("maxBodySize"));
		if ((long)corpse.size() > max)
		{
			Response	rep;
			printLogs(bod.getMethod(), bod.getPath(), bod.getVersion());
			rep.set_status(413);
			rep.set_mime("text/html");
			rep.set_body(readFile(server.getError(rep.getStatus())));
			rep.generateHeader(bod);
			rep.response();
			printAnswer(bod, rep);
			this->_response[fd] = rep.getResponse();
			throw std::invalid_argument("TOO LARGE");
		}
		string	boundary = getType(header, "boundary=", "\r\n");
		bod.setLength(bLength);
		bod.setBoundary("--" + boundary);
		bod.setBody(corpse);
	}
	bod.setHost(getType(header, "Host:", "\r\n"));
	return this->handleRequest(fd, bod, server);
}

bool	Request::handleRequest( int fd, Body &bod, Server &server )
{
	Sender			sender;
	Response		response;
	string			beforebefore;
	static string	before = "";

	response.defineStatus();
	std::string header = this->_header[fd];
    std::string requestURI = extractRequestURI(header);

	int url = server.check_url(bod.getPath());
	if (url == -1)
	{
		response.set_path(server.getError(404));
		response.set_status(404);
		return (true);
	}

    if (isPhpUri(requestURI)) 
	{
		return (this->handleCgi(fd, bod, server, response, url, header, requestURI));	
    }
	else
	{
		if (bod.getMethod() == "GET")
		{
			beforebefore = sender.handleGet(server, response, bod);
			response.getExtension();
			bod.setContent(readFile(response.getPath()));
			response.http(bod);
		}
		else if (bod.getMethod() == "POST")
			sender.postResponse(response, bod, server);
		else if (bod.getMethod() == "DELETE")
			sender.deleteResponse(response, bod, server);
		else
		{
			response.set_status(405);
			response.set_mime("text/html");
			response.set_body(generateHTML(response.getStatus(), response.description(response.getStatus())));
			response.generateHeader(bod);
			response.pushNewHeader("Allow : GET, POST, DELETE");
			response.response();
		}
		printLogs(bod.getMethod(), bod.getPath(), bod.getVersion());
		printAnswer(bod, response);
		this->_response[fd] = response.getResponse();
		before = beforebefore;
		return true;
	}
}

bool	Request::sendChunks( int &fd, Server &server )
{
	int	sent;
	
	if (this->_response.size() < BUFFER_SIZE)
		sent = send(fd, this->_response[fd].c_str(), this->_response[fd].size(), 0);
	else
		sent = send(fd, this->_response[fd].c_str(), BUFFER_SIZE, 0);
	if (sent == 0 || sent == -1)
	{
		string	number = toString(fd);
		server.setfd(fd, -1);
		close(fd);
		throw std::invalid_argument(RED "ERROR\t\t:\tClient " + number + " closed connection unexpectedly" RESET);
	}
	else
	{
		this->_sent[fd] += sent;
		if (this->_sent[fd] < this->_response[fd].size())
			return false;
		else
		{
			this->_req[fd].clear();
			this->_body[fd].clear();
			this->_header[fd].clear();
			this->_response[fd].clear();
			this->_sent[fd] = 0;
			return true;
		}
	}
	return true;
}

bool	Request::handleCgi( int fd, Body &bod, Server &server, Response &response, int url, std::string &header, std::string requestURI)
{
	    std::string scriptFile = resolveScriptFilename(server, requestURI);
        std::map<std::string,std::string> hdrs;
        parseHeadersToMap(header, hdrs);

		CGI cgi;
        cgi.setMethod(bod.getMethod());
        if (bod.getMethod() == "POST") {
            cgi.setBody(this->_body[fd]); // Body
        }
        cgi.setRequestURI(requestURI);

        if (server.getValue(url, "cgi_root").size() == 0)
		{
			response.set_path(server.getError(404));
			response.set_status(403);
			return (true);
		}
		cgi.setScriptFilename(server.getValue(url, "cgi_root") + scriptFile);     // path du fichier php
        std::string scriptName = requestURI;
        std::string::size_type qq = scriptName.find('?');
        if (qq != std::string::npos) scriptName.erase(qq);
        cgi.setScriptName(scriptName);
        std::string host = getType(header, "Host:", "\r\n");
        std::string serverName = host;
        std::string serverPort = "80";
        std::string::size_type colon = host.find(':');
        if (colon != std::string::npos)
		{
            serverName = host.substr(0, colon);
            serverPort = host.substr(colon + 1);
        }
		else 
		{
            std::string listen = server.get("listen");
            std::string::size_type c = listen.find(':');
            if (c != std::string::npos) serverPort = listen.substr(c+1);
        }
        cgi.setServerName(serverName);
        cgi.setServerPort(serverPort);
        cgi.setDocumentRoot(server.get("root"));
        for (std::map<std::string,std::string>::const_iterator it = hdrs.begin(); it != hdrs.end(); ++it)
            cgi.setHeader(it->first, it->second);
        if (!cgi.start_cgi(server.getEpFd(), fd)) {
            response.set_status(500);
            response.set_mime("text/plain");
            response.set_body("CGI start failed");
            response.generateHeader(bod);
            response.response();
            this->_response[fd] = response.getResponse();
            return true;
        }
        return false;		
}

Request::Request() : _epfd(-1) {}
Request::~Request() {}
