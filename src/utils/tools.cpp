/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:58:05 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/19 22:48:58 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Parser/Body.hpp"
#include "../Parser/Run.hpp"
#include "../Sender/Response.hpp"

void	printLogs( string method, string path, string version )
{
	Run		run;
	string	intro;

	if (method == "GET")
		intro = string(CYAN "REQUEST GET\t:\t");
	else if (method == "POST")
		intro = string(GREEN "REQUEST POST\t:\t");
	else if (method == "DELETE")
		intro = string(YELLOW "REQUEST DELETE\t:\t");
	else
		intro = string(RED"REQUEST " + method + "\t:\t");
	addEpollEvent(run.getEpoll(), STDOUT_FILENO);
	std::cout << intro + method + " " + path + " " + version << std::endl;
	std::cout << RESET;
	delEpollEvent(run.getEpoll(), STDOUT_FILENO);
}

void	printAnswer( Body &body, Response &ref )
{
	Run		run;
	string	intro;
	string	color = "";

	if (ref.getStatus() >= 400)
		color = RED;
	else
	{
		if (body.getMethod() == "GET") color = CYAN;
		else if (body.getMethod() == "POST") color = GREEN;
		else if (body.getMethod() == "DELETE") color = YELLOW;
		else { color = RED; }
	}
	if (body.getMethod() == "GET")
		intro = color + string("ANSWER GET\t:\t");
	else if (body.getMethod() == "POST")
		intro = color + string("ANSWER POST\t:\t");
	else if (body.getMethod() == "DELETE")
		intro = color + string("ANSWER DELETE\t:\t");
	else
		intro = color + string("ANSWER " + body.getMethod() + "\t:\t");
	addEpollEvent(run.getEpoll(), STDOUT_FILENO);
	std::cout << intro + body.getVersion() + " " << ref.getStatus()
		<< " " + ref.description(ref.getStatus()) + RESET << std::endl;
	std::cout << RESET;
	delEpollEvent(run.getEpoll(), STDOUT_FILENO);
}

string	readFile( string path )
{
	std::ifstream		file(path.c_str());
	std::stringstream	ss;

	if (file.is_open())
	{
		ss << file.rdbuf();
		file.close();
		return ss.str();
	}
	return "";
}

void	writeFile( string path, string content )
{
	std::ofstream	file(path.c_str());

	if (file.is_open())
	{
		file << content;
		file.close();
	}
}

void	writeDir( string file, std::vector< std::map<string, string> > c )
{
	std::ostringstream	oss;
	
	int fd = open(file.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0640);
	if (fd == -1)
		return ;
	std::map<string, string>::iterator	it;
	for (size_t i = 0; i < c.size(); i++)
	{
		for (it = c[i].begin(); it != c[i].end(); ++it)
		{
			if (it->first != "host")
				oss << it->first << "=" << it->second << " ";
		}
		oss << std::endl;
	}
	write(fd, oss.str().c_str(), oss.str().size());
	close(fd);
}

string	getType( string message, string toFind, string end )
{
	string	temp = message;
	size_t	start = temp.find(toFind), ending;

	if (start == string::npos)
		return "";
	temp = temp.c_str() + start;
	ending = temp.find(end);
	temp = temp.substr(0, ending);
	return temp.c_str() + toFind.size() + 1;
}

string	generateHTML( int status, string description )
{
	string	html;

	if (status == 204)
		return "";
	html.append("<!DOCTYPE html>");
	html.append("<style>.center{text-align: center;}</style>");
	html.append("<html><body>");
	html.append("<h1 style=\"text-align: center;\" >" + toString(status)
		+ " " + description + "</h1>");
	html.append("<div class=\"center\"><a href=\"../index.html\"><- Go back to home page</a></div>");
	html.append("<html><body>");
	return html;
}

bool	fileExist( string path )
{
	struct stat	st;
	
	if (stat(path.c_str(), &st) != 0)
		return false;
	return true;
}

bool	hasPermission( string path, int	mode )
{
	if (access(path.c_str(), mode) != 0)
		return false;
	return true;
}
