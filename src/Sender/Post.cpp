/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:47:32 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/08 13:36:09 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Post.hpp"
#define INPUT "plainTextInput"
#define CONTENT "plainTextContent"

std::vector< std::map<string, string> >	Post::_url;
std::vector< std::map<string, string> >	Post::_multipart;
std::vector< std::map<string, string> >	Post::_plain;

void	Post::urlEncoded( string body, string host )
{
	string						token, key, value;
	std::map<string, string>	tmp;
	std::istringstream			iss(body);

	while (std::getline(iss, token, '&'))
	{
		int	index = token.find('=') + 1;
		value = token.c_str() + index;
		key = token.substr(0, index - 1);
		tmp.insert(std::pair<string, string>(key, value));
		if (value == "")
			this->_empty = true;
	}
	tmp.insert(std::pair<string, string>("host", host));
	if ((this->_url.size() == 0 && not this->_empty) ||
		(find(_url.begin(), _url.end(), tmp) == _url.end()
		&& not this->_empty))
		this->_url.push_back(tmp);
	else
		this->_stored[0] = true;
}

void	Post::multipartForm( string body, string boundary, string header, string host )
{	
	size_t	i = 0;
	
	while (true)
	{
		string	toParse;
		size_t	first, second;
		first = body.find(boundary, i) + boundary.size();
		if (body.substr(first, 2) == "\r\n")
			first += 2;
		second = body.find(boundary, first);
		if (second == std::string::npos)
			break;
		toParse = body.substr(first, second - first);
		if (header.find("filename=") != string::npos)
			this->storeFile(toParse, toParse.find(CRLF));
		else
			this->storeData(toParse, toParse.find(CRLF), host);
		i = second;
	}
}

void	Post::storeData( string content, size_t head, string host )
{
	string	name = getType(content, "name=", "\"\r\n");
	std::map<string, string>	tmp;

	if (content.substr(head, 4) == "\r\n\r\n")
		head += 4;
	size_t	end = content.find("\r\n", head);
	string	value = content.substr(head, end - head);
	if (value == "")
		this->_empty = true;
	tmp.insert(std::pair<string, string>(name, value));
	if ((this->_multipart.size() == 0 && not this->_empty) ||
		(find(_multipart.begin(), _multipart.end(), tmp) == _multipart.end()
		&& not this->_empty))
	{
		tmp.insert(std::pair<string, string>("host", host));
		this->_multipart.push_back(tmp);
	}
	else
		this->_stored[0] = true;
	tmp.clear();
}

void	Post::storeFile( string content, size_t head )
{
	string	file = getType(content, "filename=", "\"\r\n"), path;
	
	if (file == "")
	{
		this->_empty = true;
		return ;
	}
	path = "upload/" + file;
	int	fd = open(path.c_str(), O_RDONLY, 0644);
	if (fd != -1) { this->_stored[1] = true; return; }
	close(fd);
	fd = open(path.c_str(), O_CREAT | O_RDWR, 0644);
	if (fd == -1) { return; }
	if (content.substr(head, 4) == "\r\n\r\n")
		head += 4;
	size_t	end = content.find("\r\n", head);
	string	inside = content.substr(head, end - head);
	writeFile(path, inside);
	close(fd);
}

Post::Post()
{
	this->_empty = false;
	this->_stored[0] = false;
	this->_stored[1] = false;
}

void	Post::textPlain( string body,  string host )
{
	std::map<string, string>	tmp;

	while (body.size() > 0)
	{
		if (body == "\r\n")
			break;
		size_t	index = body.find("\r\n"), equal;
		string	key, value, line;
		line = body.substr(0, index);
		equal = line.find("=");
		key = line.substr(0, equal);
		value = line.substr(equal + 1, index - equal);
		tmp.insert(std::pair<string, string>(key, value));
		body = body.c_str() + index + 2;
	}
	tmp.insert(std::pair<string, string>("host", host));
}

void	Post::checkException( string path )
{
	std::ifstream	file(path.c_str());

	if (not file.is_open() && path != "")
		throw Post::E403();
	if (isEmpty())
		throw Post::E200();
	if (not getFile() && not getData())
		throw Post::E201();
	if (getFile() && getData())
		throw Post::E200();
	if (getFile() && not getData())
		throw Post::E200();
	if (getData() && not getFile())
		throw Post::E200();
}
