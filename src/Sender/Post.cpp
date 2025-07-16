/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:47:32 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/16 15:45:59 by mitandri         ###   ########.fr       */
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
	if (find(_simple.begin(), _simple.end(), tmp) == _simple.end()
		&& not this->_empty)
		this->_simple.push_back(tmp);
	else
		this->_stored[0] = true;
	tmp.clear();
	tools.writeDir("upload/data.txt", this->_simple);
}

void	Post::parseComplex( string &body )
{
	Tools	tools;
	string	boundary = tools.getType(this->_message, "")
	string	multi = tools.getType(this->_message, "Content-Type:", ";");
	
	if (multi != "multipart/form-data")
		return ;
	
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
