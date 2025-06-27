/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:48:50 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/27 15:18:56 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP

#define PARSER_HPP

#include "Server.hpp"

class Parser
{
	private:
		std::vector<Server> server;
		int _socket;

		Parser(){}
		void ft_read(std::string data, std::vector<std::string> &block);
		void	get_blocks( std::vector<std::string> &block);
		int		insert_server(size_t i, std::vector<std::string> &block);
	public:
		Parser(std::string data);
		~Parser(){}	
};

int isWord(std::string const &str);
void RemoveWhiteSpace(std::string& str);
int nbr_of_words(std::string const &str);

#endif