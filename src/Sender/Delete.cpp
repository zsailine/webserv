/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:32:00 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/30 10:49:55 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Delete.hpp"

void	Delete::findResource( Server &server, string &key, string &value )
{
	for (size_t i = 0; i < this->_simple.size(); i++)
	{
		if (this->_simple[i].count(key) && this->_simple[i][key] == value
			&& this->_simple[i]["host"] == server.get("listen"))
			this->_simple[i].erase(key);
	}
}

void	Delete::deleteResource( Server &server )
{
	string	header, tmp, path;
	string	key, value;

	header = this->_message.substr(0, this->_message.find("\r\n"));
	std::istringstream	iss(header);
	iss >> tmp >> path >> tmp;
	tmp.clear();
	int	index = path.rfind("/");
	key = path.substr(1, index - 1);
	value = path.substr(index + 1, path.size() - index);
	this->findResource(server, key, value);
}

/* void	Delete::printMother()
{
	std::cout << RED;
	std::map<string, string>::iterator	it;
	for (size_t i = 0; i < this->_simple.size(); i++)
	{
		for (it = this->_simple[i].begin(); it != this->_simple[i].end(); it++)
			std::cout << "[" << it->first << "] [" << it->second << "]";
		std::cout << std::endl;
	}
	std::cout << RESET;
} */
