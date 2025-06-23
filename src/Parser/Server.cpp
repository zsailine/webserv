/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:01:59 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/23 14:49:53 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string RemoveWhiteSpace(const std::string& str)
{
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
    return (result);
}

std::map<std::string , std::string> Server::getMap() const
{
	return (_map);
}
void	Server::init_value()
{
	_map.insert(std::pair<std::string, std::string>("host", ""));
	_map.insert(std::pair<std::string, std::string>("port", ""));
}

void	Server::get_type(int number, std::string str, std::string &key, std::string &value)
{
	std::string toSplit = RemoveWhiteSpace(str);
    size_t pos = toSplit.find('=');
    if (pos == std::string::npos)
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: " << str << " is not a valid argument\n";
		throw std::exception();
	}
    key = toSplit.substr(0, pos);
    value = toSplit.substr(pos + 1);
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

static int ft_isdigit(std::string &str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	Server::check_value(int number)
{
	if (_map["host"].size() == 0)
	{
		std::cerr << "[ Server " << number << " ]\n" << "Error: host is not defined\n";
		throw std::exception();
	}
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
}

Server::Server(int number, std::vector<std::string> const &block)
{
	init_value();
	for (std::vector<std::string>::const_iterator it = block.begin(); it != block.end(); it++)
	{
		std::string key;
		std::string value;
		get_type(number, *it, key, value);
		change_value(number, key, value);
	}
	check_value(number);
}