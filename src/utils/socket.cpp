/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:07:59 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/08 11:43:50 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

int isSocket(int fd, std::vector<Server> server)
{
	for (size_t i = 0; i < server.size(); i++)
	{
		if (fd == server[i].getSocket())
			return (server[i].getIndex());
	}
	return (-1);
}
