/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:05:06 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/07 17:49:31 by mitandri         ###   ########.fr       */
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
		string	_content;
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
		string	getContent() { return this->_content; }
		string	getBody() { return this->_body; }
		string	getHeader() { return this->_header; }
		void	setLength( int l ) { this->_bodylength = l; }
		void	setMethod( string m ) { this->_method = m; }
		void	setPath( string p ) { this->_path = p; }
		void	setVersion( string v ) { this->_version = v; }
		void	setBoundary( string b ) { this->_boundary = b; }
		void	setHost( string h ) { this->_host = h; }
		void	setContent( string c ) { this->_content = c; }
		void	setBody( string b ) { this->_body = b; }
		void	setHeader( string h ) { this->_header = h; }
		void	setFirst( std::istringstream &iss )
			{ iss >> this->_method >> this->_path >> this->_version; }
		~Body() {}
};

#endif
