/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:19:53 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/01 12:39:29 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_HPP
#define DEFINE_HPP

// ========== LIBRARY ==========

#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdexcept>
#include <exception>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

// ========== COLOR ==========

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;35m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"
#define UNDERLINE "\033[4m"

// ========== VALUE ==========

#define BACKLOG 5
#define PORT 8080
#define	BUFFER 3000

// ========== HTTP RESPONSE ========== 

#define HTTP "HTTP/1.1 200 OK\n \
Content-Type: text/plain\n \
Content-Length:12\n\n \
Hello World!"

// ========== TYPEDEF ==========
typedef std::string	string;

void	signalHandler( int sigNum );

#endif
