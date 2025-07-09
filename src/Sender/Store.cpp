/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Store.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:15:29 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/09 21:30:54 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Store.hpp"

std::multimap<string, string>	Store::_storer;

void	Store::storeData( string &message )
{
	int		index = message.rfind('\n');
	string	data = message.c_str() + index + 1;
	int		count = std::count(data.begin(), data.end(), '&');

	for (int i = 0; i < (count + 1); i++)
	{
		int	j = data.find('&');
		string	temp = data.substr(0, j);
		string key, value;
		key = temp.substr(0, temp.find('='));
		value = temp.c_str() + temp.find('=') + 1;
		this->_storer.insert(std::pair<string, string>(key, value));
		data = data.substr(j + 1, data.size() - j);
	}
}

void	Store::printStorer() const
{
	for (auto it = this->_storer.begin(); it != this->_storer.end(); ++it)
		std::cout << "[" << it->first << "] [" << it->second << "]" << std::endl;
}
