/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:44:50 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/14 14:05:26 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_HPP
#define POST_HPP

#include "lib.hpp"
#include "class.hpp"

class Post
{
	protected:

		static std::vector< std::map<string, string> >	_url;
		static std::vector< std::map<string, string> >	_multipart;
		static std::vector< std::map<string, string> >	_plain;

		string	getBody();
		int	storeFile( string content, size_t head, string url );
		int	storeData( string content, size_t head, string host );

	public:

		Post() {}
		int	urlEncoded( string body, string host );
		int	textPlain( string body,  string host );
		int	octetStream( string body, string path, string url );
		int	multipartForm( string body, string boundary, string path, string host );
		virtual ~Post() {}
};

#endif
