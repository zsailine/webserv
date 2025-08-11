/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoll.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:02:38 by zsailine          #+#    #+#             */
/*   Updated: 2025/08/11 09:08:57 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib.hpp"

void addEpollEvent(int epfd, int socket)
{
	struct epoll_event event;

	event.data.fd = socket;
	event.events = EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, socket, &event);
}

void	modifyEpollEvent( int epfd, int fd, uint32_t ev )
{
	struct epoll_event event;

	event.data.fd = fd;
	event.events = ev;
	epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &event);
}


void delEpollEvent(int epfd, int socket)
{
	epoll_ctl(epfd, EPOLL_CTL_DEL, socket, NULL);
}