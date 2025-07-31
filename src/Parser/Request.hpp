/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:57:31 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/31 14:16:38 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "lib.hpp"
#include "class.hpp"

class Body;

class	Request
{
	private:
		std::map<int, string>	_header;
		std::map<int, string>	_body;
		std::map<int, string>	_req;

	public:
		Request();
		void	readChunks( int fd, Server &server );
		void	handleRequest( int fd, Body &bod, Server &server );
		void	parseRequest( int fd, string &body, int bLength, Server &server );
		string	getReq( int fd ) { return this->_req[fd]; }
		string	getHeader( int fd ) { return this->_header[fd]; }
		string	getBody( int fd ) { return this->_body[fd]; }
		~Request();
};

#endif