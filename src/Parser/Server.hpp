/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:53:57 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/23 14:44:19 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

#define SERVER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <map>

class Server
{
	private:
			std::map<std::string , std::string> _map;

			Server(){}
			void	init_value();
			void	change_value(int number, std::string &key, std::string &value);
			void	get_type(int number, std::string str, std::string &type, std::string &value);
			void	check_value(int number);
	public:
			Server(int number, std::vector<std::string> const &block);
			std::map<std::string , std::string> getMap() const;
			~Server(){}
			
};

#endif