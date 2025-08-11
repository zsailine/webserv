/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:26 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/18 14:24:43 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response( std::string const &message ) : _message(message)
{
	std::string		line;
	std::ifstream	file("./files/mimes.conf");

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

void Response::set_header(const std::string &req)
{
	Tools				tools;
	std::istringstream ss(req);
	std::string method, path, version;

	ss >> method >> path >> version;
	this->_method = method;
	this->_version = version;
	tools.printLogs(this->_method, path, this->_version);
	this->_path = path;
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

void        Response::set_path(std::string path)
{
	_path = path;
}

void	Response::set_status(int status)
{
	_status = status;
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

void	Response::run()
{
	Tools	tools;

	if (this->_method != "POST")
		this->_content = tools.readFile(this->_path);
	this->getExtension();
}

void	Response::http( int status, string file )
{
	Tools	tools;
	string description = this->description(status);

	this->_response.append(this->_version + " ");
	this->_response.append(tools.toString(status) + " ");
	this->_response.append(description + "\r\n");
	if (file == "")
	{
		this->_response.append("Content-Type: " + this->_mime + "\r\n");
		this->_response.append("Content-Length: ");
		this->_response.append(tools.toString(this->_content.size()) + "\r\n");
		this->_response.append("Connection: keep-alive\r\n\r\n");
		this->_response.append(this->_content);
	}
	else
	{
		string	content = tools.readFile(file);
		this->_response.append("Content-Type: text/html\r\n");
		this->_response.append("Content-Length: ");
		this->_response.append(tools.toString(content.size()) + "\r\n");
		this->_response.append("Connection: keep-alive\r\n\r\n");
		this->_response.append(content);
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