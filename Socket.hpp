/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 06:12:36 by mitandri          #+#    #+#             */
/*   Updated: 2025/06/20 06:47:47 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <stdexcept>
#include <exception>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;35m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"
#define UNDERLINE "\033[4m"

class Socket
{
	private:
	
		int	_socket;
	
	public:

		Socket();
		~Socket();
		
		void	startSocket();
};

#endif
