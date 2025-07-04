/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:02:47 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/04 10:33:38 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_HPP

#define LIB_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/epoll.h>

#include "../src/Parser/Parser.hpp"
#include "../src/Server/ServerResponse.hpp"


/*		EPOLL		*/
void addEpollEvent(int epfd, int socket);
void delEpollEvent(int epfd, int ocket);


#endif


