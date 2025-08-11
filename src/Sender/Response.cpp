/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:26 by aranaivo          #+#    #+#             */
/*   Updated: 2025/08/08 13:27:45 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response()
{
	std::string		line;
	std::ifstream	file("./files/conf/mimes.conf");

	if (not file.is_open())
		return ;
	while (getline(file, line))
	{
		int	index = line.find(' ');
		string	extension, mime;
		mime = line.c_str() + (index + 1);
		extension = line.substr(0, index);
		if (mime.size() && extension.size())
			this->_mimetype.insert(std::pair<string, string>(extension, mime));
	}
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

void	Response::http( Body bod, string file )
{
	string description = this->description(this->_status);

	this->_response.append(bod.getVersion() + " ");
	this->_response.append(toString(this->_status) + " ");
	this->_response.append(description + "\r\n");
	if (file == "")
	{
		this->_response.append("Content-Type: " + this->_mime + "\r\n");
		this->_response.append("Content-Length: ");
		this->_response.append(toString(bod.getContent().size()) + "\r\n");
		this->_response.append("Connection: keep-alive\r\n\r\n");
		this->_response.append(bod.getContent());
	}
	else
	{
		this->_response.append("Content-Type: text/html\r\n");
		this->_response.append("Content-Length: ");
		this->_response.append(toString(file.size()) + "\r\n");
		this->_response.append("Connection: keep-alive\r\n\r\n");
		this->_response.append(file);
	}
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
	if (status == 400) return "Bad Request";
	if (status == 401) return "Unauthorized";
	if (status == 403) return "Forbidden";
	if (status == 404) return "Not Found";
	return "Not Found";
}