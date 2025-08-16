/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:26 by aranaivo          #+#    #+#             */
/*   Updated: 2025/08/16 08:31:46 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response()
{
	this->_mimetype.insert(std::pair<string, string>(".aac", "audio/aac"));
	this->_mimetype.insert(std::pair<string, string>(".avi", "video/x-msvideo"));
	this->_mimetype.insert(std::pair<string, string>(".bin", "application/octet-stream"));
	this->_mimetype.insert(std::pair<string, string>(".bmp", "image/bmp"));
	this->_mimetype.insert(std::pair<string, string>(".css", "text/css"));
	this->_mimetype.insert(std::pair<string, string>(".doc", "application/msword"));
	this->_mimetype.insert(std::pair<string, string>(".epub", "application/epub+zip"));
	this->_mimetype.insert(std::pair<string, string>(".gif", "image/gif"));
	this->_mimetype.insert(std::pair<string, string>(".htm", "text/html"));
	this->_mimetype.insert(std::pair<string, string>(".html", "text/html"));
	this->_mimetype.insert(std::pair<string, string>(".ico", "image/vnd.microsoft.icon"));
	this->_mimetype.insert(std::pair<string, string>(".ics", "text/calendar"));
	this->_mimetype.insert(std::pair<string, string>(".jpeg", "image/jpeg"));
	this->_mimetype.insert(std::pair<string, string>(".jpg", "image/jpeg"));
	this->_mimetype.insert(std::pair<string, string>(".js", "text/javascript"));
	this->_mimetype.insert(std::pair<string, string>(".json", "application/json"));
	this->_mimetype.insert(std::pair<string, string>(".mp3", "audio/mpeg"));
	this->_mimetype.insert(std::pair<string, string>(".mp4", "video/mp4"));
	this->_mimetype.insert(std::pair<string, string>(".png", "image/png"));
	this->_mimetype.insert(std::pair<string, string>(".pdf", "application/"));
	this->_mimetype.insert(std::pair<string, string>(".php", "application/pdf"));
	this->_mimetype.insert(std::pair<string, string>(".wav", "audio/wav"));
}

void	Response::set_path(std::string index, std::string url, std::string path)
{
	if (path[path.size() - 1] == '/')
		path = path.substr(0, path.size() - 1);
	char tmp = _path.substr(url.size())[0];
	if (tmp != '/')
		_path = path + '/'  +_path.substr(url.size());
	else
		_path = path + _path.substr(url.size());
	if (isDirectory(_path))
	{
		if (_path[path.size() - 1] != '/')
			_path = _path + '/' + index;
		else
			_path += index;
	}
}

void Response::getExtension()
{
	int 	index;
	std::string	extension;
	
	index = this->_path.rfind('.');
	extension = this->_path.c_str() + index;
	if (not this->_mimetype.count(extension))
		this->_mime = "text/plain";
	else
		this->_mime = this->_mimetype[extension];
}

void	Response::http( Body bod )
{
	string description = this->description(this->_status);

	this->_response.append(bod.getVersion() + " ");
	this->_response.append(toString(this->_status) + " ");
	this->_response.append(description + "\r\n");
	this->_response.append("Content-Type: " + this->_mime + "\r\n");
	this->_response.append("Content-Length: ");
	this->_response.append(toString(bod.getContent().size()) + "\r\n");
	this->_response.append("Connection: keep-alive\r\n\r\n");
	this->_response.append(bod.getContent());
}

void	Response::generateHeader( Body bod )
{
	string	description = this->description(this->_status);

	this->_header.append(bod.getVersion() + " ");
	this->_header.append(toString(this->_status) + " ");
	this->_header.append(description + "\r\n");
	this->_header.append("Content-Type: " + this->_mime + "\r\n");
	this->_header.append("Content-Length: ");
	this->_header.append(toString(this->_body.size()) + "\r\n");
}

void	Response::pushNewHeader( string header )
{
	this->_header.append(header + "\r\n");
}

void	Response::response()
{
	this->_response = this->_header + "\r\n" + this->_body;
}

void	Response::defineStatus()
{
	this->_status = 200;
}

string	Response::description( int status )
{
	if (status == 200) return "OK";
	if (status == 201) return "Created";
	if (status == 202) return "Accepted";
	if (status == 204) return "No Content";
	if (status == 400) return "Bad Request";
	if (status == 401) return "Unauthorized";
	if (status == 403) return "Forbidden";
	if (status == 404) return "Not Found";
	if (status == 405) return "Method Not Allowed";
	if (status == 413) return "Payload Too Large";
	if (status == 431) return "Request Header Fields Too Large";
	if (status == 500) return "Internal Server Error";
	if (status == 501) return "Not Implemented";
	if (status == 505) return "HTTP Version Not Supported";
	return "Not Found";
}
