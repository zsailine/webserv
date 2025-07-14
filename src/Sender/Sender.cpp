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

void	Sender::sendMessage( std::string message, int fd )
{
	int				status = 200;
	ServerResponse	response(message);
	
	response.get_full_path(message);
	response.get_file_content();
	response.get_mime_type();
	if (open(response.get_path().c_str(), O_RDONLY) < 0)
		status = 400;
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
