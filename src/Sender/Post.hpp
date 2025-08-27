/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:44:50 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/27 11:30:59 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_HPP
#define POST_HPP

#include "lib.hpp"
#include "class.hpp"

class Post
{
	protected:

		static std::vector< std::map<string, string> >	_multipart;

		int	storeFile( string content, size_t head, string url );
		int	storeData( string content, size_t head, string host );

	public:

		Post() {}
		int	multipartForm( string body, string boundary, string path, string host );
		int	uploadFile( string body, string pat, string url );
		~Post() {}
};

#endif
