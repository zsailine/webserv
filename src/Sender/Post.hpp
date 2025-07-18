/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:44:50 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/18 10:45:17 by mitandri         ###   ########.fr       */
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
		string											_message;
		static std::vector< std::map<string, string> >	_simple;

		string	getBody();
		void	storeFile( string content, size_t head );
		void	storeData( string content, size_t head );
		void	parseContent( string content );

	public:

		Post() {}
		Post( string message );
		void	parseRequest();
		void	checkError( Response &ref, int stat );
		void	parseSimple( string &body );
		void	parseComplex( string &body );
		virtual ~Post() {}

		bool	getData() const { return this->_stored[0]; }
		bool	getFile() const { return this->_stored[1]; }
		bool	isEmpty() const { return this->_empty; }
};

#endif
