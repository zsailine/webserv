/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:05:06 by mitandri          #+#    #+#             */
/*   Updated: 2025/09/11 14:05:30 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BODY_HPP
#define BODY_HPP

#include "lib.hpp"

class Body
{
	private:
		int		_bodylength;
		string	_method;
		string	_path;
		string	_version;
		string	_boundary;
		string	_host;
		string	_content1;
		string	_header;
		string	_body;

	public:
		Body() {}
		int		getLength() { return this->_bodylength; }
		string	getMethod() { return this->_method; }
		string	getPath() { return this->_path; }
		string	getVersion() { return this->_version; }
		string	getBoundary() { return this->_boundary; }
		string	getHost() { return this->_host; }
		string	getContent1() { return this->_content1; }
		void	setContent1( string c ) { this->_content1 = c; }
		string	getBody() { return this->_body; }
		string	getHeader() { return this->_header; }
		void	setLength( int l ) { this->_bodylength = l; }
		void	setMethod( string m ) { this->_method = m; }
		void	setPath( string p ) { this->_path = p; }
		void	setVersion( string v ) { this->_version = v; }
		void	setBoundary( string b ) { this->_boundary = b; }
		void	setHost( string h ) { this->_host = h; }
		void	setBody( string b ) { this->_body = b; }
		void	setHeader( string h ) { this->_header = h; }
		void	setFirst( std::istringstream &iss )
			{ iss >> this->_method >> this->_path >> this->_version; }
		~Body() {}
};

#endif
