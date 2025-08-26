/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:47:32 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/26 15:16:53 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Post.hpp"
#define INPUT "plainTextInput"
#define CONTENT "plainTextContent"

std::vector< std::map<string, string> >	Post::_url;
std::vector< std::map<string, string> >	Post::_multipart;
std::vector< std::map<string, string> >	Post::_plain;

int	Post::urlEncoded( string body, string host )
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
	}
	tmp.insert(std::pair<string, string>("host", host));
	if (this->_url.size() == 0 ||
		(find(_url.begin(), _url.end(), tmp) == _url.end()))
		this->_url.push_back(tmp);
	else
		return 200;
	return 201;
}

int	Post::multipartForm( string body, string boundary, string path, string host )
{
	int		status;
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
		if (toParse.substr(0, toParse.find("\r\n")).find("filename=") != string::npos)
			status = this->storeFile(toParse, toParse.find(CRLF), path);
		else
			status = this->storeData(toParse, toParse.find(CRLF), host);
		if (status != 200 && status != 201)
			break;
		i = second;
	}
	return status;
}

int	Post::storeData( string content, size_t head, string host )
{
	string	name = getType(content, "name=", "\"\r\n");
	std::map<string, string>	tmp;

	if (content.substr(head, 4) == "\r\n\r\n")
		head += 4;
	size_t	end = content.find("\r\n", head);
	string	value = content.substr(head, end - head);
	tmp.insert(std::pair<string, string>(name, value));
	tmp.insert(std::pair<string, string>("host", host));
	if (this->_multipart.size() == 0 ||
		(find(_multipart.begin(), _multipart.end(), tmp) == _multipart.end()))
		this->_multipart.push_back(tmp);
	else
		return 200;
	return 201;
}

int	Post::storeFile( string content, size_t head, string url )
{
	string	file = getType(content, "filename=", "\"\r\n"), path;
	
	if (file == "")
		return 400;
	path = url + file;
	int	fd = open(path.c_str(), O_RDONLY, 0644);
	if (fd != -1) return close(fd), 200; 
	fd = open(path.c_str(), O_CREAT | O_RDWR, 0644);
	if (fd == -1) return 500;
	if (content.substr(head, 4) == "\r\n\r\n")
		head += 4;
	size_t	end = content.find("\r\n", head);
	string	inside = content.substr(head, end - head);
	writeFile(path, inside);
	close(fd);
	return 201;
}

int	Post::textPlain( string body,  string host )
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
	return 201;
}

int	Post::octetStream( string body, string path, string url )
{
	size_t	index = path.rfind('/');
	string	file = path.substr(index + 1, string::npos);

	if (file == "")
		return 400;
	path = url + file;
	int	fd = open(path.c_str(), O_RDONLY, 0644);
	if (fd != -1) return close(fd), 200; 
	close(fd);
	fd = open(path.c_str(), O_CREAT | O_RDWR, 0644);
	if (fd == -1) return 500;
	writeFile(path, body);
	close(fd);
	return 201;
}

