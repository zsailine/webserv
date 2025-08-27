/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:09:35 by aranaivo          #+#    #+#             */
/*   Updated: 2025/04/17 15:30:05 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iostream>

template <typename T>
T min (T a, T b){
    return ( (a < b) ? a : b);
};

template <typename T>
T max (T a, T b){
    return ( (a < b) ? b : a);
};

template <typename T>
void swap (T &a, T &b){
    T tmp;
    tmp = a;
    a = b;
    b = tmp;
};

#endif