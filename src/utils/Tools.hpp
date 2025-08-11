/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:52:58 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/18 11:57:28 by zsailine         ###   ########.fr       */
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
		string	readFile( string path );
		string	getType( string message, string toFind, string end );
		void	printLogs( string method, string path, string version );
		void	printAnswer( Response &ref );
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
