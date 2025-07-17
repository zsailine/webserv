/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Run.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:50:39 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/11 15:21:43 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_HPP
#define RUN_HPP

#include "lib.hpp"
#include "class.hpp"

class Run
{
	private:

		int					_client;
		int					_epoll;
		std::string			_parameter;
		struct epoll_event	_events[MAX_EVENTS];

		Run() {}

	public:

		Run( std::string const &parameter );
		~Run() {}
		void	run();
		void	runEpoll( std::vector<Server> &server );
		void	handleSocket( int fd, std::vector<Server> &server, int &index );
		void	handleClient( int fd , Server server);
};

#endif
