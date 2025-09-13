/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:01:59 by zsailine          #+#    #+#             */
/*   Updated: 2025/09/08 08:44:04 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Router.hpp"
#include "../utils/utils.hpp"

void	Server::init_value()
{
	_map.insert(std::pair<std::string, std::string>("listen", ""));
	_map.insert(std::pair<std::string, std::string>("server_name", ""));
	_map.insert(std::pair<std::string, std::string>("routes", ""));
	_map.insert(std::pair<std::string, std::string>("maxBodySize", ""));
	_map.insert(std::pair<std::string, std::string>("root", ""));
}

static int oneValue(int number, std::string const &key, std::string &str, std::string &value)
{
	size_t pos = str.find('=');
    if (key.compare("maxBodySize") == 0 || key.compare("root") == 0 )
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

void	Add(std::string &tmp)
{
	if (!ft_isdigit(tmp))
		tmp = tmp + ":80";
	else
		tmp = "0.0.0.0:" + tmp;
}
std::string change(std::string &tmp, int i)
{
	std::string result, port, str = tmp;
	size_t index = tmp.find(':');
	if (index == std::string::npos)
		Add(tmp);
	port = tmp.substr(tmp.find(':') + 1);
	if (!ft_isdigit(port) || !check_port(port))
	{
		std::cerr << "[ Server " << i << " ]\n" << "Error: listen " << str << " is not valid\n";
		throw std::exception();
	}
	result = tmp;
	return (result);
}

void	Server::ft_listen()
{
	if (_map["listen"].size() == 0)
	{
		std::cerr << "[ Server " << index << " ]\n" << "Error: listen is empty\n";
		throw std::exception();
	}
	std::istringstream iss(_map["listen"]);
    std::string tmp;
    std::vector<std::string> tab;
    while (iss >> tmp)
		tab.push_back(change(tmp, index));
	_map["listen"].clear();
	size_t i =0;
	while (i < tab.size())
	{
		_map["listen"] = _map["listen"] + tab[i] + ' ';
		i++;
	}
}

void	Server::check_value(int number)
{
	if (_map["routes"].size() == 0)
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: routes are empty\n";
		throw std::exception();
	}
	if (_map["root"].size() == 0)
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: root is not a defined\n";
		throw std::exception();
	}
	if (_map["maxBodySize"].size() == 0)
		_map["maxBodySize"] = "10000";
	if (!ft_isdigit(_map["maxBodySize"]))
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: maxBodySize is not a number\n";
		throw std::exception();
	}
	ft_listen();
	twice(index, "Server", _map["routes"]);
	twice(index, "Server", _map["server_name"]);
}

std::string			Server::get(std::string type)
{
	string	answer = _map[type];
	for (size_t i = 0; i < answer.size(); i++)
	{
		if (std::isspace(answer[i]))
		{
			answer.erase(i, 1);
			i = 0;
		}
		else
			break;
	}
	for (size_t i = answer.size() - 1; i > 0; i--)
	{
		if (std::isspace(answer[i]))
		{
			answer.erase(i, 1);
			i = answer.size() - 1;
		}
		else
			break;
	}
	return answer;
}

int Server::getIndex() const
{
	return (index);
}

void Server::closeFds()
{
	for (size_t i = 0; i < _socket.size(); i++)
	{
		close(_socket[i]);
	}
	for (size_t j = 0; j < client_fds.size(); j++)
	{
		if (client_fds[j] != -1)
			close(client_fds[j]);
	}
}

void	Server::addClient(int fd)
{
	client_fds.push_back(fd);	
}

Server::Server(const Server &toCopy)
{
	// this = &obj;
	_socket = toCopy._socket;
	_map = toCopy._map;
	_routes = toCopy._routes;
	errorPages = toCopy.errorPages;
	index = toCopy.index;
	epfd = toCopy.epfd;
}

Server::Server(int number, std::vector<std::string> const &block)
{
	index = number;
	epfd = -1;
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

const Server & Server::operator=(const Server & obj)
{
	if (this != &obj)
	{
		_map = obj._map;
		_routes = obj._routes;
		_socket = obj._socket;
		errorPages = obj.errorPages;
		index = obj.index;
		client_fds = obj.client_fds;
		epfd = obj.epfd;
	}
	return (*this);
}

std::vector<int> 	&Server::getSocket()
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

int	Server::addRoute(std::map<std::string, Router> &routes)
{
	std::stringstream split(_map["routes"]);
	std::string word;
	while (split >> word)
	{
		if (routes.count(word) == 0)
		{
			std::cerr << "[ Server " << index << " ]\n" << "Error: " << word <<  " is not a defined route\n";
			return (0);
		}
		std::map<std::string, Router>::iterator it = routes.begin();
		while (it != routes.end())
		{
			if (it->first.compare(word) == 0 && ft_repeat(it->second.getValue("url")))
			{
				if (it->second.getValue("root").size() == 0)
					it->second.setValue("root", _map["root"]);
				_routes.push_back(it->second);
			}
			it++;
		}
	}
	return (1);
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

void	Server::setfd(int target, int toChange)
{
	std::vector<int>::iterator it = std::find(client_fds.begin(), client_fds.end(), target);
	if (it != client_fds.end())
		*it = toChange;
}

std::vector<int> Server::getClientFds()
{
	return (client_fds);
}

std::string			Server::getError(int key)
{
	return (this->errorPages.getError(key));
}

void				Server::setError(Error &error)
{
	errorPages = error;
}