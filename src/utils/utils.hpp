/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:50:05 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/08 12:36:45 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP

#define UTILS_HPP

#include "class.hpp"
#include "lib.hpp"

int		nbr_of_words(std::string const &str);
int		isWord(std::string const &str);
void	RemoveWhiteSpace(std::string& str);
int		isSocket(int fd, std::vector<Server> server);
bool	ft_ends_with(const std::string& str, const std::string& suffix); 

#endif