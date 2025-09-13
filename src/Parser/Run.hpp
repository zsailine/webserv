/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Run.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:50:39 by mitandri          #+#    #+#             */
/*   Updated: 2025/09/13 10:30:24 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef RUN_HPP
#define RUN_HPP

#include "lib.hpp"
#include "class.hpp"

class	Request;
class	Server;

class Run
{
	private:

		int					_client;
		static int			_epoll;
		std::string			_parameter;
		struct epoll_event	_events[MAX_EVENTS];
		
		void	closeAll( std::vector<Server> &server );
		
		public:
		
		Run() {}
		static std::map<int, std::ifstream*> files;
		Run( std::string const &parameter );
		~Run() {}
		void	run();
		void	runEpoll( std::vector<Server> &server );
		void ft_clean_all();
		void	handleSocket( int fd, std::vector<Server> &server, int &index );
		bool	handleClient( Request &req, std::vector<Server> &server, int &fd, int &index );
		int		getEpoll() { return this->_epoll; }
};

#endif
