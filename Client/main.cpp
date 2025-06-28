/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:44:41 by mitandri          #+#    #+#             */
/*   Updated: 2025/06/28 18:47:01 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

int	main()
{
	try
	{
		Client	client;
		client.startSocket();
	}
	catch( const std::exception& e )
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
