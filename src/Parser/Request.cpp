/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:02:47 by mitandri          #+#    #+#             */
/*   Updated: 2025/09/13 15:52:44 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

std::string	Request::getError(int key)
{
	return (this->errorPages.getError(key));
}

bool	Request::readChunks( int &fd, Server &server )
{
	Run		run;
	bool	flag = false;
	char	buffer[BUFFER_SIZE];
	int		byte;

	byte = read(fd, buffer, sizeof(buffer));
	if (byte == -1)
		close(fd);
	else if (byte == 0)
	{
		close(fd);
		delEpollEvent(run.getEpoll(), fd);
	}
	else if (byte > 0)
	{
		buffer[byte] = 0;
		this->_req[fd].append(buffer, byte);
		if (this->_req[fd].find("Expect: 100-continue") != string::npos)
		{
			string	toSend = "HTTP/1.1 100 Continue\r\n\r\n";
			if (this->_continue[fd] == false)
			{
				int	b = send(fd, toSend.c_str(), toSend.size(), 0);
				this->_continue[fd] = true;
				if (b == -1)
				{
					server.setfd(fd, -1);
					close(fd);
				}
				else if (b == 0)
					delEpollEvent(run.getEpoll(), fd);
			}
		}
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

static int	checkHeader( string &header, Body &body )
{
	if (header.size() > BUFFER_SIZE)
		return 431;
	if (body.getMethod() != "GET" && body.getMethod() != "POST" && body.getMethod() != "DELETE")
		return 405;
	if (body.getVersion() != "HTTP/1.1")
		return 505;
	if (header.find("Transfer-Encoding: chunked") != string::npos)
		return 501;
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
	int	headValue = checkHeader(header, bod);
	if (headValue != 1)
	{
		Response	rep;
		printLogs(bod.getMethod(), bod.getPath(), bod.getVersion());
		rep.set_status(headValue);
		rep.set_mime("text/html");
		if (bod.getMethod() != "HEAD")
			rep.set_body(getFile(server.getError(headValue)));
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
			rep.set_body(getFile(server.getError(rep.getStatus())));
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
	
	response.defineStatus();
	std::string header = this->_header[fd];
    std::string requestURI = extractRequestURI(header);
	
	int url = server.check_url(bod.getPath());
	printLogs(bod.getMethod(), bod.getPath(), bod.getVersion());
	if (url == -1)
	{
		response.set_path(server.getError(404));
		response.set_status(404);
		response.getExtension();
		response.http(bod);
		printAnswer(bod, response);
		this->_response[fd] = response.getResponse();
		return (true);
	}
	if (server.getValue(url, "allowedMethods").find(bod.getMethod()) == string::npos)
	{
		response.set_path(server.getError(405));
		response.set_status(405);
		response.getExtension();
		response.http(bod);
		printAnswer(bod, response);
		this->_response[fd] = response.getResponse();
		return (true);
	}
    if (isCgi(requestURI) && server.getValue(url, "cgi_root").size() != 0) 
	{
		return (this->handleCgi(fd, bod, server, response, url, header, requestURI));	
    }
	else
	{
		if (bod.getMethod() == "GET")
		{
			sender.handleGet(server, response, bod);
			// response.getExtension();
			// response.http(bod);
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
		printAnswer(bod, response);
		this->_response[fd] = response.getResponse();
		return true;
	}
}

static size_t get_file_size(std::ifstream *f)
{
    f->seekg(0, std::ios::end);
    std::streampos end = f->tellg();
    f->seekg(0, std::ios::beg);
    if (end == -1) return 0;
    return static_cast<size_t>(end);
}

bool sendChunks(int &fd, ResponseData &response)
{
	Run run;
    if (!response.opened)
    {
        Run::files[fd] = new std::ifstream(response.path.c_str(), std::ios::binary);
        response.opened     = true;
        response.file_size  = get_file_size(Run::files[fd]);
        response.sent       = 0;
    }
    if (!response.header_sent)
    {
        response.header.append("Content-Length: " + toString(response.file_size) + "\r\n");
        response.header.append("Connection: close\r\n\r\n");
        response.buffer.assign(response.header.begin(), response.header.end());
        response.header_sent = true;
        response.offset = 0;
    }
    while (response.offset < response.buffer.size())
    {
        ssize_t w = send(fd,
                         response.buffer.data() + response.offset,
                         response.buffer.size() - response.offset,
                         MSG_DONTWAIT | MSG_NOSIGNAL);
        if (w <= -1)
        {
            Run::files[fd]->close();
            delete Run::files[fd];
            Run::files.erase(fd);
			close(fd);
			delEpollEvent(run.getEpoll(), fd);
			throw std::invalid_argument("");
        }
        response.offset += static_cast<size_t>(w);
    }
    if (response.offset >= response.buffer.size())
    {
        response.buffer.clear();
        response.offset = 0;
    }
    if (response.opened && response.sent < response.file_size)
    {
        char block[BUFFER_SIZE];
        size_t want = std::min<size_t>(BUFFER_SIZE,
                                       response.file_size - response.sent);
        std::streamsize got = Run::files[fd]->rdbuf()->sgetn(block, want);
        if (got > 0)
        {
            response.buffer.assign(block, block + got);
            response.offset = 0;
            response.sent        += static_cast<size_t>(got);
        }
        else
        {
            Run::files[fd]->close();
            delete Run::files[fd];
            Run::files.erase(fd);
            response.opened = false;
        }
    }
    if (response.buffer.empty() && !response.opened)
    {
        return true;
    }

    return false;
}


bool	Request::ft_send( int &fd )
{
	Run	run;
	int	sent = 1;

	if (_response[fd].response.size() == 0)
	{
		if (sendChunks(fd, _response[fd]) ==  false)
		{
			return false;
		}
	}
	else
		sent = send(fd, this->_response[fd].response.c_str(), this->_response[fd].response.size(), 0);
	if (sent <= 0)
	{
		close(fd);
		throw std::invalid_argument("");
	}
	this->_req[fd].clear();
	this->_body[fd].clear();
	this->_header[fd].clear();
	this->_sent[fd] = 0;
	return true;
}

bool	Request::handleCgi( int fd, Body &bod, Server &server, Response &response, int url, std::string &header, std::string requestURI)
{
	    std::string scriptFile = resolveScriptFilename(requestURI);
        std::map<std::string,std::string> hdrs;
        parseHeadersToMap(header, hdrs);

		CGI cgi;
        cgi.setMethod(bod.getMethod());
        if (bod.getMethod() == "POST") {
            cgi.setBody(this->_body[fd]); // Body
        }
        cgi.setRequestURI(requestURI);
		std::string uri = server.getValue(url, "url");
		scriptFile = "/" + scriptFile.substr(uri.size());
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
        if (!cgi.start_cgi(*this, server.getEpFd(), fd)) {
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

Request::Request() {}
Request::~Request() {}
