/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:26 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/16 14:03:44 by mitandri         ###   ########.fr       */
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

void Response::get_full_path(const std::string &req)
{
	Tools				tools;
	std::istringstream ss(req);
	std::string method, path, version;

	ss >> method >> path >> version;
	this->_method = method;	
	this->_version = version;
	tools.printLogs(this->_method, this->_path, this->_version);
	if (path == "/")
		path = "/index.html";
	this->_path = "www" + path;
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

	this->get_full_path(this->_message);
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