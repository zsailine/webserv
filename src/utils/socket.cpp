/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:07:59 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/01 13:11:53 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

int isSocket(int fd, std::vector<Server> server)
{
	for (size_t i = 0; i < server.size(); i++)
	{
		std::cout << "fd is " << fd << " toCmp is " << server[i].getSocket() << " index is " << server[i].getIndex() << std::endl;;
		if (fd == server[i].getSocket())
			return (server[i].getIndex());
	}
	return (-1);
}
