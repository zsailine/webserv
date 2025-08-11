/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:58:05 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/04 14:20:30 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Parser/Body.hpp"
#include "../Sender/Response.hpp"

void	printLogs( string method, string path, string version )
{
	string	intro;

	if (method != "GET" && method != "POST" && method != "DELETE")
		return ;
	if (method == "GET")
		intro = string(CYAN "REQUEST GET\t:\t");
	if (method == "POST")
		intro = string(GREEN "REQUEST POST\t:\t");
	if (method == "DELETE")
		intro = string(YELLOW "REQUEST DELETE\t:\t");
	std::cout << intro + method + " " + path + " " + version << std::endl;
	std::cout << RESET;
}

void	printAnswer( Body &body, Response &ref )
{
	string	intro;

	if (body.getMethod() != "GET" && body.getMethod() != "POST" && body.getMethod() != "DELETE")
		return ;
	if (body.getMethod() == "GET")
		intro = string(CYAN "ANSWER GET\t:\t");
	if (body.getMethod() == "POST")
		intro = string(GREEN "ANSWER POST\t:\t");
	if (body.getMethod() == "DELETE")
		intro = string(YELLOW "ANSWER DELETE\t:\t");
	std::cout << intro + body.getVersion() + " " << ref.getStatus()
		<< " " + ref.description(ref.getStatus()) + RESET << std::endl;
	std::cout << RESET;
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
	int		start = temp.find(toFind), ending;

	temp = temp.c_str() + start;
	ending = temp.find(end);
	temp = temp.substr(0, ending);
	return temp.c_str() + toFind.size() + 1;
}
