/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:41:42 by zsailine          #+#    #+#             */
/*   Updated: 2025/09/08 08:25:17 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

static int isDollar(std::string &str)
{
	if (nbr_of_words(str) != 1)
	{
		std::cerr << "Error: The configuration file is not correct\n";
		throw std::exception();
	}
	RemoveWhiteSpace(str);
	if (str[0] != '$' || str.size() < 6)
	{
		std::cerr << "Error: The configuration file is not correct\n";
		throw std::exception();
	}
	if (!str.compare("$server"))
	{
		return (1);
	}
	if (!str.compare("$errorPages"))
		return (3);
	std::string part = str.substr(0, 6);
	if (!part.compare("$route"))
		return (2);
	std::cerr << "Error: The configuration file is not correct\n";
	throw std::exception();
	return (0);
}

static int ft_continue(std::string str)
{
	if (!isWord(str))
		return (1);
	RemoveWhiteSpace(str);
	if (str[0] != '$')
		return (1);
	return (0);
}

void Parser::ft_read(std::string data, std::vector<std::string> &block)
{
	std::ifstream ifs(data.c_str());
	if (ifs.is_open())
	{
		std::string tmp;
		while (getline(ifs, tmp))
		{
			block.push_back(tmp);
		}
		ifs.close();
	}
	else
	{
		std::cerr << "Error: " << data << " doesn't exist\n";
		throw std::exception();		
	}
}

int Parser::insert_server(size_t i, std::vector<std::string> &block)
{
	i++;
	static int number = 0;
	std::vector<std::string> blocks;

	while (i < block.size())
	{
		if (!ft_continue(block[i]))
		{
			server.push_back(Server(number++, blocks));
			return (i);
		}
		blocks.push_back(block[i]);
		i++;
	}
	server.push_back(Server(number++, blocks));
	return (i);
}

int Parser::insert_error(size_t i, std::vector<std::string> &block)
{
	i++;
	static int number = 0;
	std::vector<std::string> blocks;
	if (number != 0)
	{
		std::cerr  << "[ Error ]\n" << "errorPages has already been initialized\n";
		throw std::exception();
	}
	while (i < block.size())
	{
		if (!ft_continue(block[i]))
		{
			number++;
			errorPages = Error(blocks);
			return (i);
		}
		blocks.push_back(block[i]);
		i++;
	}
	number++;
	errorPages = Error(blocks);
	return (i);
}

int Parser::insert_route(size_t i, std::string name, std::vector<std::string> &block)
{
	i++;
	std::vector<std::string> blocks;
	RemoveWhiteSpace(name);
	if (routes.count(name) != 0)
	{
		std::cerr << "[ Route ]\n" << "Error: " << name << " is already define\n";
		throw std::exception();
	}
	while (i < block.size())
	{
		if (!ft_continue(block[i]))
		{
			routes.insert(std::pair<std::string, Router>(name, Router(name, blocks)));
			return (i);
		}
		blocks.push_back(block[i]);
		i++;
	}
	routes.insert(std::pair<std::string, Router>(name, Router(name, blocks)));
	return (i);
}

void	Parser::init_socket()
{
	size_t i = 0;
	while (i < server.size())
	{
		if (!server[i++].init_socket())
		{
			closeFds();
			throw std::exception();
		}
	}
}

void	Parser::closeFds()
{
	size_t i = 0;
	while (i < server.size())
	{
		server[i++].closeFds();
	}
}
void	Parser::get_blocks( std::vector<std::string> &block)
{
	size_t i = 0;
	while (i < block.size())
	{
		int type;
		if (isWord(block[i]) && (type = isDollar(block[i])))
		{
			if (type == 1)
			{
				i = insert_server(i, block);
			}
			else if (type == 2)
			{
				i = insert_route(i, block[i].substr(1), block);
			}
			else if (type == 3)
				i = insert_error(i, block);
		}
		else if (!isWord(block[i]))
		{
			i++;
		}
	}
	if (server.size() == 0)
	{
		std::cerr << "Error\nThere is no server\n";
		throw std::exception();
	}
}

void	Parser::addRoute()
{
	size_t i = 0;
	while (i < server.size())
	{
		if (!server[i++].addRoute(routes))
		{
			closeFds();
			throw std::exception();
		}
	}
}

void	Parser::addError()
{
	size_t i = 0;
	while (i < server.size())
	{
		server[i++].setError(errorPages);
	}
}
std::vector<Server> &Parser::getServer()
{
	return (server);
}

Parser::Parser(std::string data)
{
	std::vector<std::string> block;
	ft_read(data, block);
	get_blocks(block);
	init_socket();
	addRoute();
	addError();
}