/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:55:45 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/25 09:40:18 by zsailine         ###   ########.fr       */
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

bool ft_ends_with(const std::string& str, const std::string& suffix) 
{
    if (str.length() < suffix.length())
        return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

bool ft_starts_with(const std::string& str, const std::string& prefix)
{
    if (str.length() < prefix.length())
        return false;
    return str.compare(0 , prefix.length(), prefix) == 0;
}
int ft_atoi(std::string number)
{
	std::stringstream iss(number);
	int tmp;
	iss >> tmp;
	return (tmp);
}

int isDirectory(std::string str)
{
	int i = str.size() - 1;
	while (str[i] != '/')
	{
		if (str[i] == '.')
			return (0);
		i--;
	}
	return (1);
}

int ft_isdigit(std::string &str)
{
	int i = 0;
	if (str.size() == 0)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int ft_exist(std::string path)
{
	int			fd;
	
	fd = open(path.c_str(), O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

// std::string	getFileExtension( string const )
