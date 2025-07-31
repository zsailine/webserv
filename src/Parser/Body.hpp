/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:05:06 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/31 14:16:04 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BODY_HPP
#define BODY_HPP

#include "lib.hpp"
#include "class.hpp"

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

	public:
		Body() {}
		int		getLength() { return this->_bodylength; }
		string	readFile( string path );
		string	getMethod() { return this->_method; }
		string	getPath() { return this->_path; }
		string	getVersion() { return this->_version; }
		string	getBoundary() { return this->_boundary; }
		string	getHost() { return this->_host; }
		string	getContent() { return this->_content; }
		void	setLength( int l ) { this->_bodylength = l; }
		void	setMethod( string m ) { this->_method = m; }
		void	setPath( string p ) { this->_path = p; }
		void	setVersion( string v ) { this->_version = v; }
		void	setBoundary( string b ) { this->_method = b; }
		void	setHost( string h ) { this->_host = h; }
		void	setContent( string c ) { this->_content = c; }
		void	setFirst( std::istringstream &iss )
			{ iss >> this->_method >> this->_path >> this->_version; }
		~Body() {}
};

#endif
