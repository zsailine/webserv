/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:55:45 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/04 16:11:20 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

int afterEquals(int pos, std::string str)
{	pos++;
	while (str[pos])
	{
		if (str[pos] > 32)
			return (1);
		pos++;
	}
	return (0);
}

int isWord(std::string const &str)
{
	if (str.size() == 0)
		return (0);
	return (1);
}

int nbr_of_words(std::string const &str)
{
	int count = 0;
	std::string word;
	std::stringstream split(str);
	while (split >> word)
	  count++;
	return (count);
}

void RemoveWhiteSpace(std::string& str)
{
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}