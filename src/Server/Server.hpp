/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:53:57 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/01 13:19:24 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

#define SERVER_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <exception>
#include <algorithm>
#include <map>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>


class Server
{
	private:
	std::map<std::string , std::string> _map;
	int	_socket;
	int index;
	
	std::vector<int> client_fds;
	Server(){}
	void	init_value();
	void	change_value(int number, std::string &key, std::string &value);
	int		get_type(int number, std::string str, std::string &type, std::string &value);
	void	check_value(int number);
	sockaddr_in init_adress();
	public:
		Server(int number, std::vector<std::string> const &block);
		~Server(){}
		Server(const Server &toCopy);
		
		void init_socket();
		int getSocket() const;
		int getIndex() const;
		void	closeFds();
	
};

#include "../utils/utils.hpp"

#endif