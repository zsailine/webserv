/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:01:59 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/20 16:00:43 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string RemoveWhiteSpace(const std::string& str)
{
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
    return (result);
}

void	Server::init_value()
{
	host = "";
	port = "";
}

int	Server::get_type(std::string str, std::string &type, std::string &value)
{
	
}

void	Server::change_value(int number, std::string &type,std::string &key, std::string &value)
{
	if (key.size() != 0)
	{
		std::cerr << "[Server " << number << " ]\n" << "Error: " << type << " has already a value\n";
		throw std::exception();
	}
	key = value;
}

Server::Server(int number, std::vector<std::string> const &block)
{
	init_value();
	for (std::vector<std::string>::const_iterator it = block.begin(); it != block.end(); it++)
	{
		std::string type;
		std::string value;
		get_type(*it, type, value);
		change_value(number)
	}
}