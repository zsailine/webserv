/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:26 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/08 14:18:35 by mitandri         ###   ########.fr       */
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

void ServerResponse::get_full_path(const std::string &req)
{
	std::istringstream ss(req);
	std::string method;
	std::string path;
	std::string version;

	ss >> method >> path >> version;
	if (path == "/")
		path = "/index.html";
	_path = "www" + path;
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

void ServerResponse::make_Http_response(int status) 
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

ServerResponse::~ServerResponse()
{
}
