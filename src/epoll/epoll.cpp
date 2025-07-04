/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoll.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:02:38 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/20 14:01:21 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib.hpp"

void addEpollEvent(int epfd, int socket)
{
	struct epoll_event event;

	event.data.fd = socket;
	event.events = EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, socket, &event);
	std::cout << "Socket " << socket << " has been successfully added to epoll.\n";
}


void delEpollEvent(int epfd, int socket)
{
	epoll_ctl(epfd, EPOLL_CTL_DEL, socket, NULL);
	std::cout << "Socket " << socket << " has been successfully deleted to epoll.\n";
}