/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:01:59 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/07 16:21:26 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Router.hpp"


void	Server::init_value()
{
	_map.insert(std::pair<std::string, std::string>("host", ""));
	_map.insert(std::pair<std::string, std::string>("port", ""));
	_map.insert(std::pair<std::string, std::string>("server_name", ""));
	_map.insert(std::pair<std::string, std::string>("routes", ""));
}

static int oneValue(int number, std::string const &key, std::string &str, std::string &value)
{
	size_t pos = str.find('=');
    if (key.compare("routes") != 0 && key.compare("server_name"))
	{
		std::string value = str.substr(pos + 1);
		if (nbr_of_words(value) > 1)
		{
			std::cerr << "[ Route " << number << " ]\n" << "Error: " << key << " can only have one value\n";
			throw std::exception();
		}
		RemoveWhiteSpace(str);
		pos = str.find('=');
		value = str.substr(pos + 1);
	}
	value = str.substr(pos + 1);
	return 1;
}

int	Server::get_type(int number, std::string tmp, std::string &key, std::string &value)
{
	if (tmp.size() == 0)
		return (0);
	std::string str = tmp;
	RemoveWhiteSpace(str);
    size_t pos = str.find('=');
    if (pos == std::string::npos || !afterEquals(pos, str) || str[pos + 1] == '=')
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: " << tmp << " is not a valid argument\n";
		throw std::exception();
	}
    key = str.substr(0, pos);
	oneValue(number, key, tmp, value);
	return (1);
}

void	Server::change_value(int number, std::string &key, std::string &value)
{
	if (!_map.count(key))
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: " << key << " is not a valid type\n";
		throw std::exception();
	}
	if (_map[key].size() != 0)
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: " << key << " has already a value\n";
		throw std::exception();
	}
	_map[key] = value;
}

static int twice(int index, std::string str)
{
	std::istringstream iss(str);
    std::string tmp;
    std::set<std::string> tab;

    while (iss >> tmp)
	{
        if (tab.count(tmp))
        {
			std::cerr << "[ Server " << index << " ]\n" << "Error: " << tmp << " is called more than one time\n";
			throw std::exception();
		}
		else
            tab.insert(tmp);
    }
	return (1);
}

void	Server::check_value(int number)
{
	if (_map["host"].size() == 0)
		_map["host"] = "0.0.0.0";
	if (_map["port"].size() == 0)
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: port is not defined\n";
		throw std::exception();
	}
	if (!ft_isdigit(_map["port"]))
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: port is invalid\n";
		throw std::exception();
	}
	if (!valid_host(_map["host"]))
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: host is invalid\n";
		throw std::exception();
	}
	twice(index, _map["routes"]);
	if (_map["routes"].size() == 0)
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: routes are empty\n";
		throw std::exception();
	}
}

int Server::getIndex() const
{
	return (index);
}

void Server::closeFds()
{
	close(_socket);
}

void	Server::addClient(int fd)
{
	client_fds.push_back(fd);	
}

Server::Server(const Server &toCopy)
{
	_socket = toCopy._socket;
	_map = toCopy._map;
	index = toCopy.index;
}

Server::Server(int number, std::vector<std::string> const &block)
{
	index = number;
	init_value();
	for (std::vector<std::string>::const_iterator it = block.begin(); it != block.end(); it++)
	{
		std::string key;
		std::string value;
		if (get_type(number, *it, key, value))
			change_value(number, key, value);
	}
	check_value(number);
}

int Server::getSocket() const
{
	return (_socket);
}

void	Server::addRoute(std::map<std::string, Router> routes)
{
	std::stringstream split(_map["routes"]);
	std::string word;
	while (split >> word)
	{
		if (routes.count(word) == 0)
		{
			std::cerr << "[ Server " << index << " ]\n" << "Error: " << word <<  " is not a defined route\n";
			throw std::exception();
		}
		std::map<std::string, Router>::iterator it = routes.begin();
		while (it != routes.end())
		{
			if (it->first.compare(word) == 0)
			{
				_routes.push_back(it->second);
			}
			it++;
		}
	}
}