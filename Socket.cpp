/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 06:14:22 by mitandri          #+#    #+#             */
/*   Updated: 2025/06/20 06:21:43 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket() : _socket() {}

Socket::~Socket()
{
	close(this->_socket);
}

void	Socket::startSocket()
{
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket < 0)
		throw (std::invalid_argument(RED "Literally no " RESET));
}
