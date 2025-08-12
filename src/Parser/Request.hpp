/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:57:31 by mitandri          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/04 14:16:52 by mitandri         ###   ########.fr       */
=======
/*   Updated: 2025/08/11 15:05:13 by mitandri         ###   ########.fr       */
>>>>>>> mitandri
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
<<<<<<< HEAD
		string					_response;
=======
		std::map<int, string>	_response;
>>>>>>> mitandri
		std::map<int, string>	_header;
		std::map<int, string>	_body;
		std::map<int, string>	_req;

	public:
		Request();
		bool	readChunks( int fd, Server &server );
<<<<<<< HEAD
		bool	handleRequest( Body &bod, Server &server );
=======
		bool	handleRequest( int fd, Body &bod, Server &server );
>>>>>>> mitandri
		bool	parseRequest( int fd, string &body, int bLength, Server &server );
		bool	sendChunks( int fd );
		string	getReq( int fd ) { return this->_req[fd]; }
		string	getHeader( int fd ) { return this->_header[fd]; }
		string	getBody( int fd ) { return this->_body[fd]; }
<<<<<<< HEAD
		string	getResponse() { return this->_response; }
=======
		string	getResponse( int fd ) { return this->_response[fd]; }
>>>>>>> mitandri
		~Request();
};

#endif