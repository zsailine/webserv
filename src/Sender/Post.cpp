/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:47:32 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/27 12:14:57 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Post.hpp"

std::vector<std::map<string, string> >	Post::_multipart;

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
	Run		run;
	string	file = getType(content, "filename=", "\"\r\n"), path;
	
	if (file == "")
		return 400;
	path = url + file;
	int	fd = open(path.c_str(), O_RDONLY, 0644);
	if (fd != -1)
	{
		addEpollEvent(run.getEpoll(), fd);
		close(fd);
		delEpollEvent(run.getEpoll(), fd);
		return 200; 
	}
	fd = open(path.c_str(), O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return 500;
	addEpollEvent(run.getEpoll(), fd);
	if (content.substr(head, 4) == "\r\n\r\n")
		head += 4;
	size_t	end = content.find("\r\n", head);
	string	inside = content.substr(head, end - head);
	writeFile(path, inside);
	delEpollEvent(run.getEpoll(), fd);
	close(fd);
	return 201;
}


int	Post::uploadFile( string body, string path, string url )
{
	Run		run;
	size_t	index = url.rfind('/');
	string	file = url.substr(index + 1, string::npos);
	string	destination;

	if (index == string::npos || file == "")
		return 400;
	if (not ft_ends_with(path, "/") && not ft_starts_with(file, "/"))
		path.push_back('/');
	destination = path + file;
	if (fileExist(destination))
		return 200;
	int	fd = open(destination.c_str(), O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return 500;
	addEpollEvent(run.getEpoll(), fd);
	writeFile(destination, body);
	close(fd);
	delEpollEvent(run.getEpoll(), fd);
	return 201;
}
