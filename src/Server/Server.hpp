/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:53:57 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/11 15:41:20 by zsailine         ###   ########.fr       */
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
#include <set>

class Router;

class Server
{
	private:
		std::map<std::string , std::string> _map;
		std::vector<Router> _routes;
		std::vector<int>	_socket;
		int index;
		
		std::vector<int> client_fds;
		void		init_value();
		void		change_value(int number, std::string &key, std::string &value);
		int			get_type(int number, std::string str, std::string &type, std::string &value);
		void		check_value(int number);
		void		ft_listen();
		int			ft_repeat(std::string url);
		int 		socketer(std::string tmp);

	public:
		Server(){}
		Server(int number, std::vector<std::string> const &block);
		const Server & operator=(const Server & obj);
		~Server(){}
		Server(const Server &toCopy);
		
		void				addRoute(std::map<std::string, Router> routes);
		void 				init_socket();
		std::vector<int> 	&getSocket();
		int 				getIndex() const;
		void				closeFds();
		void				addClient(int fd);
		std::vector<Router> &getRoutes();
		int 				check_url(std::string url);
		std::string 		getValue(int index, std::string key);
		std::vector<int> 	getClientFds();
};

#include "../utils/utils.hpp"

int ft_isdigit(std::string &str);
int valid_host(std::string &str);
int afterEquals(int pos, std::string str);
int	check_port(std::string &port);
template<typename T>
int twice(T index, std::string type ,std::string str)
{
	std::istringstream iss(str);
    std::string tmp;
    std::set<std::string> tab;

    while (iss >> tmp)
	{
        if (tab.count(tmp))
        {
			std::cerr << "[ " << type << " " << index << " ]\n" << "Error: " << tmp << " is called more than one time\n";
			throw std::exception();
		}
		else
            tab.insert(tmp);
    }
	return (1);
}


#include "Router.hpp"

#endif