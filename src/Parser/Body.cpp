/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:56:12 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/31 14:19:05 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Body.hpp"

string	Body::readFile( string path )
{
	Run		poll;
	char	buffer[BUFFER_SIZE];
	int		fd = open(path.c_str(), O_RDONLY);
	
	if (fd == -1)
		return "";
	addEpollEvent(poll.getEpoll(), fd);
	size_t	byte = read(fd, buffer, sizeof(buffer));
	if (byte > 0)
		this->_content.append(buffer, byte);
	else if (byte == 0)
		close(fd);
	else
		close(fd);
	return this->_content;
}
