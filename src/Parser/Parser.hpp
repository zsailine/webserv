/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:48:50 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/18 13:43:27 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP

#define PARSER_HPP

#include "../Server/Router.hpp"
#include "../Server/Server.hpp"

class Parser
{
	private:
		std::vector<Server> 			server;
		std::map<std::string, Router> 	routes;
		Error							errorPages;
		

		Parser(){}
		void	ft_read(std::string data, std::vector<std::string> &block);
		void	get_blocks( std::vector<std::string> &block);
		int		insert_server(size_t i, std::vector<std::string> &block);
		int		insert_route(size_t i, std::string name, std::vector<std::string> &block);
		int		insert_error(size_t i, std::vector<std::string> &block);
		void	init_socket();
		void	addRoute();
		void	addError();
	public:
		Parser(std::string data);
		~Parser(){}
		std::vector<Server> &getServer();
		void closeFds();
};

int isWord(std::string const &str);
void RemoveWhiteSpace(std::string& str);
int nbr_of_words(std::string const &str);
int ft_atoi(std::string number);

#endif