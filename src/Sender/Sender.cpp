/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:23:21 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/14 12:42:20 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sender.hpp"

void	Sender::getMessage( std::string message, int fd )
{
	ServerResponse	response(message);
	
	response.run();
	this->defineStatus();
	if (response.getMethod() == "GET")
		this->getResponse(response);
	if (response.getMethod() == "POST")
		this->postResponse(message, response);
	if (response.getMethod() == "DELETE")
		this->deleteResponse();
	this->sendMessage(fd);
}

void	Sender::defineStatus()
{
	this->_status = 200;
	this->_description = "OK";
}

void	Sender::getResponse( ServerResponse &ref )
{
	std::ostringstream	response;

	response	<< ref.getVersion() << " "
				<< this->_status << " " << this->_description << "\r\n"
				<< "Content-Type: " << ref.getMime() << "\r\n"
				<< "Content-Length: " << ref.getContent().size() << "\r\n"
				<< "\r\n" << ref.getContent();
	this->_response = response.str();
}

void	Sender::postResponse( std::string &message, ServerResponse &ref )
{
	Store	store;

	store.parsePost(message);
	(void) ref;
}

void	Sender::deleteResponse()
{
}

void	Sender::sendMessage( int fd )
{
	size_t	size;

	size = this->_response.size();
	send(fd, this->_response.c_str(), size, 0);
}

int	Sender::getStatus() const {	return this->_status; }
