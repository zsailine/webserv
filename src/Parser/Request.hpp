/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:57:31 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/11 15:05:13 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "lib.hpp"
#include "class.hpp"
#include "../utils/utils.hpp"

class Body;

class	Request
{
	private:
		std::map<int, string>	_response;
		std::map<int, string>	_header;
		std::map<int, string>	_body;
		std::map<int, string>	_req;

	public:
		Request();
		bool	readChunks( int fd, Server &server );
		bool	handleRequest( int fd, Body &bod, Server &server );
		bool	parseRequest( int fd, string &body, int bLength, Server &server );
		bool	sendChunks( int fd );
		string	getReq( int fd ) { return this->_req[fd]; }
		string	getHeader( int fd ) { return this->_header[fd]; }
		string	getBody( int fd ) { return this->_body[fd]; }
		string	getResponse( int fd ) { return this->_response[fd]; }
		~Request();
};

#endif