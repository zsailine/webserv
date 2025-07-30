/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:50:05 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/30 13:47:15 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP

#define UTILS_HPP

// #include "class.hpp"
#include "lib.hpp"

int			nbr_of_words(std::string const &str);
int			isWord(std::string const &str);
void		RemoveWhiteSpace(std::string& str);
bool		ft_ends_with(const std::string& str, const std::string& suffix);
bool		ft_starts_with(const std::string& str, const std::string& prefix);
int			isDirectory(std::string str);
int 		ft_exist(std::string path);
long long	ft_atoi(std::string number);
int			ft_isdigit(std::string &str);
int			afterEquals(int pos, std::string str);

#endif