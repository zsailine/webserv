/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 08:22:27 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/08 12:15:40 by mitandri         ###   ########.fr       */
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
			throw(std::invalid_argument(RED "Need two arguments at most" RESET));
		(ac == 1) ? parameter = "config/test.conf" : parameter = av[1];
		Run	start(parameter);
		start.run();
	}
	catch( const std::exception& e )
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
