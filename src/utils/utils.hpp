/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:50:05 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/04 10:23:12 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP

#define UTILS_HPP

#include <string>
#include <sstream>
#include <algorithm>
#include "../Server/Server.hpp"

int		nbr_of_words(std::string const &str);
int		isWord(std::string const &str);
void	RemoveWhiteSpace(std::string& str);
int		isSocket(int fd, std::vector<Server> server);
bool ft_ends_with(const std::string& str, const std::string& suffix); 

#endif