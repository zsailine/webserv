/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:55:45 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/04 10:22:45 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

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

bool ft_ends_with(const std::string& str, const std::string& suffix) 
{
    if (str.length() < suffix.length())
        return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}