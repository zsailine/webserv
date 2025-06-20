/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:53:57 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/20 15:55:39 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

#define SERVER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>

class Server
{
	private:
			std::string host;
			std::string port;
			Server(){}
			void	init_value();
			void	change_value(int number, std::string &type, std::string &key, std::string &value);
			int	get_type(std::string str, std::string &type, std::string &value);
	public:
			Server(int number, std::vector<std::string> const &block);
			~Server(){}
			
};

#endif