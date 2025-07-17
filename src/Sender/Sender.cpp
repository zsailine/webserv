/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:23:21 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/17 10:59:12 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sender.hpp"

void	Sender::getMessage( std::string message, int fd )
{
	Response	response(message);
	
	response.run();
	response.defineStatus();
	if (response.getMethod() == "GET")
		response.http(response.getStatus(), "");
	if (response.getMethod() == "POST")
		this->postResponse(message, response);
	if (response.getMethod() == "DELETE")
		this->deleteResponse();
	this->sendMessage(fd, response.getResponse());
}

void	Sender::postResponse( string &message, Response &ref )
{
	Post	post(message);

	post.parseRequest();
	post.checkError(ref, ref.getStatus());
	// if (post.isEmpty()) { ref.http(stat, "./files/empty.html"); return ; }
	// // if (post.getData() && not post.getFile())
	// (post.getData()) ? ref.http(stat, "./files/presentData.html")
	// 	: ref.http(stat, "./files/newData.html");
	// (post.getFile()) ? ref.http(stat, "./files/presentFile.html")
	// 	: ref.http(stat, "./files/newFile.html");
	// if (not post.getFile() && not post.getData())
	// 	ref.http(stat, "./files/newData.html");
}

void	Sender::deleteResponse()
{
}

void	Sender::sendMessage( int fd, string message )
{
	size_t	size;

	size = message.size();
	send(fd, message.c_str(), size, 0);
}
