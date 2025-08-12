/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:32:00 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/08 13:53:05 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Delete.hpp"

void	Delete::findResource( string host, string &key, string &value )
{
	for (size_t i = 0; i < this->_url.size(); i++)
	{
		if (this->_url[i].count(key) && this->_url[i][key] == value
			&& this->_url[i]["host"] == host)
			this->_url[i].erase(key);
	}
}

void	Delete::deleteResource( string host, string header )
{
	string	tmp, path;
	string	key, value;

	std::istringstream	iss(header);
	iss >> tmp >> path >> tmp;
	tmp.clear();
	int	index = path.rfind("/");
	key = path.substr(1, index - 1);
	value = path.substr(index + 1, path.size() - index);
	std::cout << RED;
	std::cout << "key [" << key << "] [" << value << "]" << std::endl;
	std::cout << RESET;
	this->findResource(host, key, value);
}
