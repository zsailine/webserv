/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:47:32 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/18 10:17:54 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Post.hpp"

std::vector< std::map<string, string> >	Post::_simple;

void	Post::parseRequest()
{
	Tools	tools;
	string	type = tools.getType(this->_message,
			"Content-Type:", "\r\n");
	string	body = getBody();

	if (type == "application/x-www-form-urlencoded")
		this->parseSimple(body);
	else
		this->parseComplex(body);
}

void	Post::parseSimple( string &body )
{
	Tools						tools;
	string						token, key, value;
	std::map<string, string>	tmp;
	std::istringstream			iss(body);

	while (std::getline(iss, token, '&'))
	{
		int	index = token.find('=') + 1;
		value = token.c_str() + index;
		key = token.substr(0, index);
		tmp.insert(std::pair<string, string>(key, value));
		if (value == "")
			this->_empty = true;
	}
	if ((this->_simple.size() == 0 && not this->_empty) ||
		(find(_simple.begin(), _simple.end(), tmp) == _simple.end()
		&& not this->_empty))
		this->_simple.push_back(tmp);
	else
		this->_stored[0] = true;
	tmp.clear();
	tools.writeDir("upload/data.txt", this->_simple);
}

void	Post::parseComplex( string &body )
{
	Tools	tools;
	string	boundary = tools.getType(this->_message, "boundary", "\r\n");
	string	multi = tools.getType(this->_message, "Content-Type:", ";");
	
	if (multi != "multipart/form-data")
		return ;
	boundary.insert(0, "--");
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
		this->parseContent(toParse);
		i = second;
	}
}

void	Post::parseContent( string content )
{
	Tools	tools;
	size_t	head = content.find("\r\n\r\n");
	string	header = content.substr(0, head);
	string	name = tools.getType(header, "name", ";");
	
	if (name != "\"myFile\"")
		this->storeData(content, head);
	else
		this->storeFile(content, head);
}

void	Post::storeData( string content, size_t head )
{
	Tools	tools;
	string	name = tools.getType(content, "name=", "\"\r\n");
	std::map<string, string>	tmp;

	if (content.substr(head, 4) == "\r\n\r\n")
		head += 4;
	size_t	end = content.find("\r\n", head);
	string	value = content.substr(head, end - head);
	if (value == "")
		this->_empty = true;
	tmp.insert(std::pair<string, string>(name, value));
	if ((this->_simple.size() == 0 && not this->_empty) ||
		(find(_simple.begin(), _simple.end(), tmp) == _simple.end()
		&& not this->_empty))
		this->_simple.push_back(tmp);
	else
		this->_stored[0] = true;
	tmp.clear();
	tools.writeDir("upload/data.txt", this->_simple);
}

void	Post::storeFile( string content, size_t head )
{
	Tools	tools;
	string	file = tools.getType(content, "filename=", "\"\r\n"), path;
	
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
	if (fd == -1)
		return;
	if (content.substr(head, 4) == "\r\n\r\n")
		head += 4;
	size_t	end = content.find("\r\n", head);
	string	inside = content.substr(head, end - head);
	write(fd, inside.c_str(), inside.size());
	close(fd);
}
void	Post::checkError( Response &ref, int stat )
{
	if (isEmpty())
	{
		ref.http(stat, "./files/empty.html");
		return ;
	}
	if (not getFile() && not getData())
	{
		ref.http(stat, "./files/newData.html");
		return ;
	}
	if (getFile() && getData())
	{
		ref.http(stat, "./files/presentData.html");
		return ;
	}
	if (getFile() && not getData())
	{
		ref.http(stat, "./files/presentFile.html");
		return ;
	}
	if (getData() && not getFile())
	{
		ref.http(stat, "./files/presentData.html");
		return ;
	}
}

string	Post::getBody()
{
	string	temp = this->_message;
	int		start = temp.find("\r\n\r\n") + 4;

	return temp.substr(start);
}

Post::Post( string message )
{
	this->_message = message;
	this->_empty = false;
	this->_stored[0] = false;
	this->_stored[1] = false;
}
