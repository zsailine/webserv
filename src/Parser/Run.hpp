/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Run.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:50:39 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/11 09:14:51 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		int					_epoll;
		std::string			_parameter;
		struct epoll_event	_events[MAX_EVENTS];

		Run() {}

	public:

		static int			_epoll;
		std::string			_parameter;
		struct epoll_event	_events[MAX_EVENTS];

		void	closeAll( std::vector<Server> &server );

	public:

		Run() {}
		Run( std::string const &parameter );
		~Run() {}
		void	run();
		void	runEpoll( std::vector<Server> &server );
		void	handleSocket( int fd, std::vector<Server> &server, int &index );
		void	handleClient( int fd , Server &server);
};
#endif
