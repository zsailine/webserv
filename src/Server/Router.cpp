/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:33:07 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/08 10:15:43 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"

void	Router::init_value()
{
	_map.insert(std::pair<std::string, std::string>("url", ""));
	_map.insert(std::pair<std::string, std::string>("root", ""));
	_map.insert(std::pair<std::string, std::string>("allowedMethods", ""));
}

static int oneValue(std::string const &name, std::string const &key, std::string &str, std::string &value)
{
	size_t pos = str.find('=');
    if (key.compare("allowedMethods") != 0)
	{
		std::string value = str.substr(pos + 1);
		if (nbr_of_words(value) > 1)
		{
			std::cerr << "[ Route " << name << " ]\n" << "Error: " << key << " can only have one value\n";
			throw std::exception();
		}
		RemoveWhiteSpace(str);
		pos = str.find('=');
		value = str.substr(pos + 1);
	}
	value = str.substr(pos + 1);
	return 1;
}

int	Router::get_type(std::string const &name, std::string tmp, std::string &key, std::string &value)
{
	if (tmp.size() == 0)
		return (0);
	std::string str = tmp;
	RemoveWhiteSpace(str);
    size_t pos = str.find('=');
    if (pos == std::string::npos || !afterEquals(pos, str) || str[pos + 1] == '=')
	{
		std::cerr << "[ Route " << name << " ]\n" << "Error: " << tmp << " is not a valid argument\n";
		throw std::exception();
	}
    key = str.substr(0, pos);
	oneValue(name, key, tmp, value);
	return (1);
}

void	Router::change_value(std::string const &name, std::string &key, std::string &value)
{
	if (!_map.count(key))
	{
		std::cerr << "[ Route " << name << " ]\n" << "Error: " << key << " is not a valid type\n";
		throw std::exception();
	}
	if (_map[key].size() != 0)
	{
		std::cerr << "[ Route " << name << " ]\n" << "Error: " << key << " has already a value\n";
		throw std::exception();
	}
	_map[key] = value;
}

static int valid(std::string index, std::string type ,std::string str)
{
	std::istringstream iss(str);
    std::string tmp;
    std::set<std::string> tab;

    while (iss >> tmp)
	{
        if (tmp.compare("GET") != 0 && tmp.compare("POST") != 0
			&& tmp.compare("DELETE") != 0)
        {
			std::cerr << "[ " << type << " " << index << " ]\n" << "Error: " << tmp << " is not a valid method\n";
			throw std::exception();
		}
		else
            tab.insert(tmp);
    }
	return (1);
}

void	Router::check_value(std::string const &name)
{
	if (_map["url"].size() == 0 || _map["url"][0] != '/')
	{
		std::cerr << "[ Route " << name << " ]\n" << "Error: url is not defined\n";
		throw std::exception();
	}
	if (_map["root"].size() == 0)
	{
		std::cerr << "[ Route " << name << " ]\n" << "Error: root is not defined\n";
		throw std::exception();
	}
	if (_map["allowedMethods"].size() == 0)
	{
		std::cerr << "[ Route " << name << " ]\n" << "Error: allowedMethods is not defined\n";
		throw std::exception();
	}
	twice(name, "Route", _map["allowedMethods"]);
	valid(name, "Route", _map["allowedMethods"]);
}

Router::Router(const Router &toCopy)
{
	_map = toCopy._map;
}

Router::Router(std::string const &name, std::vector<std::string> block)
{
	init_value();
	for (std::vector<std::string>::const_iterator it = block.begin(); it != block.end(); it++)
	{
		std::string key;
		std::string value;
		if (get_type(name, *it, key, value))
			change_value(name, key, value);
	}
	check_value(name);
}

std::map<std::string , std::string> Router::getMap() const
{
	return _map;
}

std::string Router::getValue(std::string key)
{
	return (_map[key]);
}