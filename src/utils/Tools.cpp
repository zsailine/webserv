/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:58:05 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/30 15:15:55 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tools.hpp"

#define SIZE 4096

void	Tools::printLogs( string method, string path, string version )
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

void	Tools::printAnswer( Response &ref )
{
	string	intro;

	if (ref.getMethod() != "GET" && ref.getMethod() != "POST" && ref.getMethod() != "DELETE")
		return ;
	if (ref.getMethod() == "GET")
		intro = string(CYAN "ANSWER GET\t:\t");
	if (ref.getMethod() == "POST")
		intro = string(GREEN "ANSWER POST\t:\t");
	if (ref.getMethod() == "DELETE")
		intro = string(YELLOW "ANSWER DELETE\t:\t");
	std::cout << intro + ref.getVersion() + " " << ref.getStatus()
		<< " " + ref.description(ref.getStatus()) + RESET << std::endl;
	std::cout << RESET;
}

string	Tools::readFile( string path )
{
	int			fd;
	char		buffer[4096];
	ssize_t		bytes_read;
	std::string	content;
	
	fd = open(path.c_str(), O_RDONLY);
	if (fd == -1)
		return "";
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
		content.append(buffer, bytes_read);
	close(fd);
	return (content);
}

void	Tools::writeDir( string file, std::vector< std::map<string, string> > c )
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

string	Tools::getType( string message, string toFind, string end )
{
	string	temp = message;
	int		start = temp.find(toFind), ending;

	temp = temp.c_str() + start;
	ending = temp.find(end);
	temp = temp.substr(0, ending);
	return temp.c_str() + toFind.size() + 1;
}

string	Tools::readChunk( int fd )
{
	int	i = 0;
	string	result = "";

	while (true)
	{
		char	buffer[SIZE];
		size_t	byte = read(fd, buffer, SIZE);
		if (i == 2)
			break;
		std::cout << RED << byte << "           " << i << RESET << std::endl;
		result.append(buffer, byte);
		if (result.find("\r\n\r\n") && result.find("Content-Length:") == string::npos)
			break;
		i++;
	}
	return result;
}
