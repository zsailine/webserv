/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:23:21 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/17 11:05:46 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sender.hpp"

void	Sender::handleGet(int fd, Server &server, ServerResponse &response)
{
	int				status = 200;
	int url = server.check_url(response.get_path());
	std::cout << "The url is " << url << std::endl;
	if (url == -1)
		return;
	std::string path = server.getValue(url, "root");

	response.set_path(server.getValue(url, "index"), server.getValue(url, "url"),  path);
	response.get_file_content();
	response.get_mime_type();
	if (open(response.get_path().c_str(), O_RDONLY) < 0)
		status = 404;
	response.make_Http_response(status);
	send(fd, response.get_response().c_str(), response.get_response().size(), 0);
}

void	Sender::handleRequest( std::string message, int fd, Server &server )
{
	ServerResponse	response(message);
	std::string     request;

	response.set_header(message);
	if (response.get_method() == "GET")
		handleGet(fd, server, response);

}

void	Sender::httpResponse()
{
	
}

int	Sender::getStatus() const
{
	return this->_status;
}
