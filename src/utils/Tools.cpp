/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:58:05 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/17 13:17:46 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tools.hpp"

void	Tools::printLogs( string method, string path, string version )
{
	string	intro;

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
			oss << it->first << "=" << it->second << " ";
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
