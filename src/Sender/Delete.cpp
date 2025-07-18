/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:32:00 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/18 11:19:52 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Delete.hpp"

void	Delete::deleteResource()
{
	string	header, tmp, path;

	header = this->_message.substr(0, this->_message.find("\r\n"));
	std::istringstream	iss(header);
	iss >> tmp >> path >> tmp;
	tmp.clear();
	std::cout << RED << "[" << path << "]" << std::endl;
}

void	Delete::printMother()
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
}
