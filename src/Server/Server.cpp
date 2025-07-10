/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:01:59 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/10 10:18:37 by zsailine         ###   ########.fr       */
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
    if (key.compare("host") == 0)
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
	if (_map["routes"].size() == 0)
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: routes are empty\n";
		throw std::exception();
	}
	twice(index, "Server", _map["routes"]);
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

std::vector<Router> &Server::getRoutes()
{
	return (_routes);
}

int		Server::ft_repeat(std::string url)
{
	size_t i = 0;
	while (i < _routes.size())
	{
		if (url.compare(_routes[i].getValue("url")) == 0)
		{
			std::cerr << "[ Server " << index << " ]\n" << "Error: Some routes have the same url\n";
			throw std::exception();
		}
		i++;
	}
	return (1);
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
			if (it->first.compare(word) == 0 && ft_repeat(it->second.getValue("url")))
			{
				_routes.push_back(it->second);
			}
			it++;
		}
	}
}

std::string Server::getValue(int index, std::string key)
{
	return (_routes[index].getValue(key));
}

static int for_url(std::string &str, std::string &toCmp)
{
	int size = -1;
	std::string tmp = str.substr(0, toCmp.size());
	if (str[toCmp.size() - 1] != '/' && str[toCmp.size()] && str[toCmp.size()] != '/')
		return (size);
	if (tmp.compare(toCmp) == 0)
		size = toCmp.size();
	return (size);
}

int Server::check_url(std::string url)
{
	size_t i = 0;
	int index = -1;
	int size = -1;
	while (i < _routes.size())
	{
		std::string str = getValue(i, "url");
		if (url.size() >= str.size())
		{
			int tmp = for_url(url, str);
			if (tmp > size)
			{
				size = tmp;
				index = i;
			}
		}
		i++;
	}
	return (index);
}