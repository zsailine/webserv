/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:57:31 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/25 15:09:36 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "lib.hpp"
#include "class.hpp"
#include "../utils/utils.hpp"
//#include "../utils/tools.cpp"

class Body;

class	Request
{
	private:
		int _epfd;
	public:
		std::map<int, string>	_response;
		std::map<int, string>	_header;
		std::map<int, string>	_body;
		std::map<int, string>	_req;
		std::map<int, size_t>	_sent;
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
		void 	setEpollFd(int epfd) { _epfd = epfd; }
		~Request();
};

#endif