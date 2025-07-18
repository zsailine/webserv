/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:50:05 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/18 14:00:02 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP

#define UTILS_HPP

// #include "class.hpp"
#include "lib.hpp"

int		nbr_of_words(std::string const &str);
int		isWord(std::string const &str);
void	RemoveWhiteSpace(std::string& str);
bool	ft_ends_with(const std::string& str, const std::string& suffix);
int		isDirectory(std::string str);
int 	ft_exist(std::string path);
int		ft_atoi(std::string number);
int		ft_isdigit(std::string &str);
int		afterEquals(int pos, std::string str);

#endif