/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:23:21 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/11 15:19:00 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sender.hpp"

void	Sender::sendMessage( std::string message, int fd, Server server )
{
	int				status = 200;
	ServerResponse	response(message);
	std::string     request;


	response.get_full_path(message);
	int url = server.check_url(response.get_path());
	if (url == -1)
		return;
	std::string path = server.getValue(url, "root");


	//response.set_path(path);
	std::cout << "****************" << std::endl;
	std::cout << response.get_path() << std::endl;
	std::cout << url << std::endl;
	std::cout << path << std::endl;
	std::cout << "****************" << std::endl;
	response.get_file_content();
	response.get_mime_type();
	if (open(response.get_path().c_str(), O_RDONLY) < 0)
		status = 404;
	response.make_Http_response(status);
	send(fd, response.get_response().c_str(), response.get_response().size(), 0);

}

void	Sender::httpResponse()
{
	
}

int	Sender::getStatus() const
{
	return this->_status;
}
