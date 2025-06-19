/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:11:19 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/17 13:46:45 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#define PORT 8080
#define BUF_SIZE 4096
#define MAX_EVENTS 2

#include "lib.hpp"

int main()
{
	ServerSocket socket1(8080);
	int epoll = epoll_create(1);
	// epoll_event events[2];
	addEpollEvent(epoll, socket1.getSocket());
	std::cout << "epoll is " << epoll << std::endl; 
	std::cout << "socket is at " << socket1.getSocket() << std::endl;
	delEpollEvent(epoll, socket1.getSocket());            
	return (0);
}