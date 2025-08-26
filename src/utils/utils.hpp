/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:50:05 by zsailine          #+#    #+#             */
/*   Updated: 2025/08/26 12:54:05 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef UTILS_HPP

#define UTILS_HPP

#include "lib.hpp"
#include "../Sender/Response.hpp"
#include "../Parser/Body.hpp"

class Response;
class Server;

bool		hasPermission( string path, int	mode );
bool		fileExist( string path );
int			nbr_of_words(std::string const &str);
int			isWord(std::string const &str);
void		RemoveWhiteSpace(std::string& str);
bool		ft_ends_with(const std::string& str, const std::string& suffix);
bool		ft_starts_with(const std::string& str, const std::string& prefix);
int			isDirectory(std::string str);
int 		ft_exist(std::string path);
long long	ft_atoi(std::string number);
int			ft_isdigit(std::string &str);
int			afterEquals(int pos, std::string str);
string		readFile( string path );
string		getType( string message, string toFind, string end );
void		writeFile( string path, string content );
void		printAnswer( Body &body, Response &ref );
void		printLogs( string method, string path, string version );
string		generateHTML( int status, string description );
void		writeDir( string file, std::vector< std::map<string, string> > c );
bool		isPhpUri(const std::string &uri);
std::string extractRequestURI(const std::string &header);
void 		parseHeadersToMap(const std::string &header, std::map<std::string,std::string> &out);
std::string resolveScriptFilename(Server &server, const std::string &uri);
std::string loadErrorPage(int code);



template<typename T>
string	toString( T number )
{
	std::stringstream	ss;
	ss << number;
	return ss.str();
}

#endif