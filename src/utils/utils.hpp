/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:50:05 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/01 13:11:59 by zsailine         ###   ########.fr       */
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

#endif