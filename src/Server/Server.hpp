/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:53:57 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/08 08:21:42 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

#define SERVER_HPP

#include "lib.hpp"

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
		void	addClient(int fd);
	
};

#include "../utils/utils.hpp"

int ft_isdigit(std::string &str);
int valid_host(std::string &str);
int afterEquals(int pos, std::string str);


#endif