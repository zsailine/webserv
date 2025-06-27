/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 04:03:41 by mitandri          #+#    #+#             */
/*   Updated: 2025/06/27 15:38:16 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static void	startTest()
{
	Server	sockets;

	sockets.startSocket();
	sockets.listenSocket();
	sockets.whileSocket();
}

int	main()
{
	try
	{
		startTest();
	}
	catch( const std::exception& e )
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
