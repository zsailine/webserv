/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:07:59 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/11 15:18:56 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

int isSocket(int fd, std::vector<Server> server)
{
	for (size_t i = 0; i < server.size(); i++)
	{
		if (std::find(server[i].getSocket().begin(), server[i].getSocket().end(), fd) != server[i].getSocket().end())
			return (server[i].getIndex());
	}
	return (-1);
}
