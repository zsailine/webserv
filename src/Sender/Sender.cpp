/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:23:21 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/08 11:35:42 by mitandri         ###   ########.fr       */
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

int	Sender::getStatus() const
{
	return this->_status;
}
