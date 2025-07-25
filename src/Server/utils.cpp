/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:42:36 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/18 13:59:01 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	check_port(std::string &port)
{
	std::stringstream str(port);
	int nbr;

	str >> nbr;
	if (nbr > 65535)
	{
		return (0);
	}
	return (1);
}

static int	only_number(std::string const &str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			i++;
			if (str[i] == 0 || str[i] < '0' || str[i] > '9')
				return (1);
		}
		if (str[i] != '.' && (str[i] < '0' || str[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

int valid_host(std::string &str)
{
	if (only_number(str))
		return (0);
	std::istringstream is(str);
	std::string word;

	while (std::getline(is, word, '.'))
	{
		std::istringstream tmp(word);
		int value;
		tmp >> value;
	}
	return (1);
}