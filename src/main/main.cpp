/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 08:22:27 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/26 09:33:59 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.hpp"
#include "class.hpp"

int	main( int ac, char **av )
{
	try
	{
		std::string	parameter;
		
		if (ac > 2)
		{
			std::cout << RED "Need two arguments at most" RESET << std::endl;
			throw std::exception();
		}
		(ac == 1) ? parameter = "config/default.conf" : parameter = av[1];
		Run	start(parameter);
		start.run();
	}
	catch( const std::exception& e ) {}
	return 0;
}
