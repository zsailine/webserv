/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:02:47 by zsailine          #+#    #+#             */
/*   Updated: 2025/08/16 08:18:53 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_HPP
#define LIB_HPP

// ========== INCLUDE ==========

#include <stdio.h>
#include <dirent.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <exception>
#include <algorithm>
#include <map>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <signal.h>

// ========== COLOR ==========

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define PIPGREEN "\033[1;5;32m"
#define BLUE "\e[1;34m"
#define PURPLE "\033[1;95m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"
#define UNDERLINE "\033[4m"

#define MAX_EVENTS 4
#define MAX_SIZE 5000
#define BUFFER_SIZE 8192
#define CRLF "\r\n\r\n"

typedef std::string	string;

/*		EPOLL		*/
void	addEpollEvent(int epfd, int socket);
void	delEpollEvent(int epfd, int ocket);
void	modifyEpollEvent( int epfd, int fd, uint32_t ev );

#endif


