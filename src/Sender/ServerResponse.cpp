/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:26 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/10 13:41:14 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerResponse.hpp"

ServerResponse::ServerResponse( std::string const &message ) : _message(message)
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

void ServerResponse::get_full_path(const std::string &req)
{
	std::istringstream ss(req);
	std::string method;
	std::string path;
	std::string version;

	ss >> method >> path >> version;
	this->_method = method;	
	this->_version = version;
	if (this->_method == "GET")
		std::cout << CYAN "LOGS GET : " << this->_method << " " << path << " " << this->_version << RESET << std::endl;
	if (this->_method == "POST")
		std::cout << GREEN "LOGS POST : " << this->_method << " " << path << " " << this->_version << RESET << std::endl;
	if (this->_method == "DELETE")
		std::cout << YELLOW "LOGS DELETE : " << this->_method << " " << path << " " << this->_version << RESET << std::endl;
	if (path == "/")
		path = "/index.html";
	this->_path = "www" + path;
}

std::string	ServerResponse::get_file_content( std::string path )
{
	int			fd;
	char		buffer[4096];
	std::string	content;
	ssize_t		bytes_read;
	
    fd = open(path.c_str(), O_RDONLY);
	if (fd == -1)
		return "";
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
		content.append(buffer, bytes_read);
	if (bytes_read == -1)
		perror("read");
	close(fd);
	this->_content = content;
	return (content);
}

void ServerResponse::getExtension()
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

void	ServerResponse::run()
{
	this->get_full_path(this->_message);
	if (this->_method != "POST")
		this->get_file_content(this->_path);
	this->getExtension();
}

std::string	ServerResponse::getPath() const { return this->_path; }

std::string	ServerResponse::getContent() const { return this->_content; }

std::string	ServerResponse::getMime() const { return this->_mime; }

std::string	ServerResponse::getResponse() const { return this->_response; }

std::string	ServerResponse::getVersion() const { return this->_version; }

std::string	ServerResponse::getMethod() const { return this->_method; }

ServerResponse::~ServerResponse() {}
