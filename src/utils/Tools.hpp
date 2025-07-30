/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:52:58 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/30 13:45:06 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "class.hpp"
#include "lib.hpp"

class Response;

class Tools
{
	private:
	
	public:

		Tools() {}
		~Tools() {}
		string	readChunk( int fd );
		string	readFile( string path );
		string	getType( string message, string toFind, string end );
		void	printAnswer( Response &ref );
		void	printLogs( string method, string path, string version );
		void	writeDir( string file, std::vector< std::map<string, string> > c );
		
		template<typename T>
		string	toString( T number )
		{
			std::stringstream	ss;
			ss << number;
			return ss.str();
		}
};

#endif
