/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:44:50 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/11 13:11:41 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_HPP
#define POST_HPP

#include "lib.hpp"
#include "class.hpp"

class Post
{
	protected:

		bool											_stored[2];
		bool											_empty;
		static std::vector< std::map<string, string> >	_url;
		static std::vector< std::map<string, string> >	_multipart;
		static std::vector< std::map<string, string> >	_plain;

		void	storeFile( string content, size_t head );
		void	storeData( string content, size_t head, string host );

	public:

		Post();
		void	urlEncoded( string body, string host );
		void	multipartForm( string body, string boundary, string header, string host );
		void	textPlain( string body,  string host );
		void	checkException( string path );
		virtual ~Post() {}

		bool	getData() const { return this->_stored[0]; }
		bool	getFile() const { return this->_stored[1]; }
		bool	isEmpty() const { return this->_empty; }

		class	E200 : public std::exception
		{ virtual const char*	what() const throw() { return ""; } };
		class	E201 : public std::exception
		{ virtual const char*	what() const throw() { return ""; } };
		class	E204 : public std::exception
		{ virtual const char*	what() const throw() { return ""; } };
		class	E400 : public std::exception
		{ virtual const char*	what() const throw() { return ""; } };
		class	E403 : public std::exception
		{ virtual const char*	what() const throw() { return ""; } };
		class	E404 : public std::exception
		{ virtual const char*	what() const throw() { return ""; } };
};

#endif
