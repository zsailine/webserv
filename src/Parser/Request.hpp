/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:57:31 by mitandri          #+#    #+#             */
/*   Updated: 2025/09/14 08:44:38 by zsailine         ###   ########.fr       */
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
		std::map<int, ResponseData>	_response;
		std::map<int, string>	_header;
		std::map<int, string>	_body;
		std::map<int, string>	_req;
		std::map<int, size_t>	_sent;
		std::map<int, bool>		_continue;
		std::vector<int>		_sockets;
		std::vector<int>		_clients;	
		Error					errorPages;
		
	public:
		Request();
		bool	handleCgi(int fd, Body &bod, Server &server, Response &response, int url, std::string &header, std::string requestURI);
		bool	readChunks( int &fd, Server &server);
		bool	handleRequest( int fd, Body &bod, Server &server );
		bool	parseRequest( int fd, string &body, int bLength, Server &server );
		bool	ft_send( int &fd );
		string	getReq( int fd ) { return this->_req[fd]; }
		string	getHeader( int fd ) { return this->_header[fd]; }
		string	getBody( int fd ) { return this->_body[fd]; }
		ResponseData	getResponse( int fd ) { return this->_response[fd]; }
		void 	setResponse(int fd, const std::string &resp) 
		{
			_response[fd].done = true;
			_response[fd].response = resp;
			_sent[fd] = 0;
    	}
		void	setError(Error error) { errorPages = error;}
		void	setSocket(std::vector<Server> &server)
		{
			for (size_t i = 0 ; i < server.size(); i++)
			{
				std::vector<int> tab = server[i].getSocket();
				for (size_t j = 0; j < tab.size(); j++)
					_sockets.push_back(tab[j]);
			}
		}
		void	addClient(int fd){ _clients.push_back(fd);}
		void	closeSocket() { for (size_t i = 0; i < _sockets.size(); i++) close(_sockets[i]);}
		void	closeClient() { for (size_t i = 0; i < _clients.size(); i++) close(_clients[i]);}
		std::string	getError(int key);
		~Request();
};

#endif