/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:56:23 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/21 14:27:34 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"

void	Error::init_value()
{
	_map.insert(std::pair<int, std::string>(404, ""));
	_map.insert(std::pair<int, std::string>(401, ""));
	_map.insert(std::pair<int, std::string>(403, ""));
	_map.insert(std::pair<int, std::string>(400, ""));
}

static int oneValue(int &key, std::string &str, std::string &value)
{
	size_t pos = str.find('=');
	std::string tmp = str.substr(pos + 1);
	if (nbr_of_words(tmp) > 1)
	{
		std::cerr << "[ errorPages " << " ]\n" << "Error: " << key << " can only have one value\n";
		throw std::exception();
	}
	RemoveWhiteSpace(str);
	pos = str.find('=');
	value = str.substr(pos + 1);
	return 1;
}

int	Error::get_type(std::string tmp, int &key, std::string &value)
{
	if (tmp.size() == 0)
		return (0);
	std::string str = tmp;
	RemoveWhiteSpace(str);
    size_t pos = str.find('=');
    if (pos == std::string::npos || !afterEquals(pos, str) || str[pos + 1] == '=')
	{
		std::cerr << "[ errorPages ]\n" << "Error: " << tmp << " is not a valid argument\n";
		throw std::exception();
	}
	std::string toCheck = str.substr(0, pos);
	if (!ft_isdigit(toCheck))
	{
		std::cerr << "[ errorPages ]\n" << "Error: " << toCheck << " must be a number\n";
		throw std::exception();
	}
    key = ft_atoi(toCheck);
	oneValue(key, tmp, value);
	return (1);
}

void	Error::change_value(int &key, std::string &value)
{
	if (!_map.count(key))
	{
		std::cerr << "[ errorPages ]\n" << "Error: " << key << " is not a valid type\n";
		throw std::exception();
	}
	if (_map[key].size() != 0)
	{
		std::cerr << "[ errorPages ]\n" << "Error: " << key << " has already a value\n";
		throw std::exception();
	}
	_map[key] = value;
}

static std::string ft_add(int key)
{
	std::stringstream is;

	is << key;
	std::string result = "www/errorPages/" + is.str() + ".html";
	return (result);
}

void	Error::check_value()
{
	for(std::map<int , std::string>::iterator it = _map.begin(); it != _map.end(); it++)
	{
		if (it->second.size() == 0)
			it->second = ft_add(it->first);
	}
	for(std::map<int , std::string>::iterator it = _map.begin(); it != _map.end(); it++)
	{
		if (!ft_exist(it->second))
		{
			std::cerr << "[ errorPages ]\n" << "Error: " << it->first << "'s file doesn't exist\n";
			throw std::exception();
		}
		if (!ft_ends_with(it->second, ".html"))
		{
			std::cerr << "[ errorPages ]\n" << "Error: " << it->first << "'s file must be an html extension\n";
			throw std::exception();
		}
	}
}

Error::Error(const Error &toCopy)
{
	_map = toCopy._map;
}

Error::Error(std::vector<std::string> block)
{
	init_value();
	for (std::vector<std::string>::const_iterator it = block.begin(); it != block.end(); it++)
	{
		int			key;
		std::string value;
		if (get_type(*it, key, value))
			change_value(key, value);
	}
	check_value();
}

Error::Error()
{
	init_value();
	check_value();
}
Error	&Error::operator=(const Error &toCopy)
{
	_map = toCopy._map;
	return (*this);
}
std::map<int , std::string> Error::getMap() const
{
	return _map;
}

std::string Error::getError(int value)
{
	return (_map[value]);
}