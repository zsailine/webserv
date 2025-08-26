/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:57:31 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/26 09:46:39 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
		std::map<int, size_t>	_sent;
	public:
		Request();
		bool	handleCgi(int fd, Body &bod, Server &server, Response &response, int url, std::string &header, std::string requestURI);
		bool	readChunks( int &fd, Server &server);
		bool	handleRequest( int fd, Body &bod, Server &server );
		bool	parseRequest( int fd, string &body, int bLength, Server &server );
		bool	sendChunks( int &fd, Server &server );
		string	getReq( int fd ) { return this->_req[fd]; }
		string	getHeader( int fd ) { return this->_header[fd]; }
		string	getBody( int fd ) { return this->_body[fd]; }
		string	getResponse( int fd ) { return this->_response[fd]; }
		void 	setResponse(int fd, const std::string &resp) 
		{
			_response[fd] = resp;
			_sent[fd] = 0;
    	}
		~Request();
};

#endif