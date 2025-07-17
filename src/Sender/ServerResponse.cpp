/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:26 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/17 13:32:31 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ServerResponse.hpp"

ServerResponse::ServerResponse(std::string buffer) : _buffer(buffer)
{
	std::string		line;
	std::ifstream	file("./../../files/mimes.conf");

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

ServerResponse::ServerResponse(ServerResponse const &toCopy)
{
	_buffer = toCopy._buffer;
	_path = toCopy._path;
	_content = toCopy._content;
	_mime = toCopy._mime;
	_method = toCopy._method;
	_response = toCopy._response;
}

void ServerResponse::set_header(const std::string &req)
{
	std::istringstream ss(req);
	std::string version;

	ss >> _method >> _path >> version;
}

void	ServerResponse::set_path(std::string index, std::string url, std::string path)
{
	std::cout << "The first path is " << _path << std::endl;
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
	std::cout << "The new path is " << _path << std::endl;
}

void ServerResponse::get_file_content()
{
	int fd;
	char buffer[4096];
	std::string content;
	ssize_t bytes_read;
    
    fd = open(_path.c_str(), O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return;
	}

	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
		content.append(buffer, bytes_read);

	if (bytes_read == -1)
		perror("read");

	close(fd);
	_content = content;
}

void ServerResponse::get_mime_type()
{
    if (ft_ends_with(_path , ".html"))
	{
		_mime = "text/html";
		return;
	}
    if (ft_ends_with(_path , ".css"))
	{
		_mime = "text/css";
		return;
	}
    if (ft_ends_with(_path , ".js"))
	{
		_mime = "application/javascript";
		return;
	}
    if (ft_ends_with(_path , ".png")) 
	{
		_mime = "image/png";
		return;
	}
    if (ft_ends_with(_path , ".jpg") || ft_ends_with(_path , ".jpeg")) 
	{
		_mime = "image/jpeg";
		return;
	}
	_mime = "text/plain";
}

void ServerResponse::
make_Http_response(int status) 
{
    std::ostringstream response;
    
    response << "HTTP/1.1 " << status << " " << (status == 200 ? "OK" : "Not Found") << "\r\n"
             << "Content-Type: " << _mime << "\r\n"
             << "Content-Length: " << _content.size() << "\r\n"
             << "Connection: close\r\n"
             << "\r\n"
             << _content;
    _response = response.str();
}

std::string ServerResponse::get_path()
{
    return _path;
}

std::string ServerResponse::get_content()
{
    return _content;
}

std::string ServerResponse::get_mime()
{
    return _mime;
}

std::string ServerResponse::get_response()
{
    return _response;
}

std::string ServerResponse::get_method()
{
	return _method;
}
ServerResponse::~ServerResponse()
{
}
