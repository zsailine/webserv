/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:41:42 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/27 16:02:38 by zsailine         ###   ########.fr       */
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

	number++;
	while (i < block.size())
	{
		if (!ft_continue(block[i]))
		{
			Server tmp = Server(number, blocks);
			server.push_back(tmp);
			return (i);
		}
		blocks.push_back(block[i]);
		i++;
	}
	Server tmp = Server(number, blocks);
	server.push_back(tmp);
	return (i);
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
				i = insert_server(i, block);
			else
			{
				i++;
			}
		}
		else if (!isWord(block[i]))
		{
			i++;
		}
	}
	server[0].init_socket();
	server[1].init_socket();
	std::cout << "Socket " << server[0].getSocket() << " has been created\n";
	std::cout << "Socket " << server[1].getSocket() << " has been created\n";
}

Parser::Parser(std::string data)
{
	std::vector<std::string> block;
	ft_read(data, block);
	get_blocks(block);
}