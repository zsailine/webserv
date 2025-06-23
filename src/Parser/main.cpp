/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:28:25 by zsailine          #+#    #+#             */
/*   Updated: 2025/06/23 14:50:03 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main()
{
	try
	{
		/* code */
		std::vector<std::string> block;
		block.push_back("host = localhost");
		block.push_back("port = 808a");
		Server server(1, block);
		std::map<std::string , std::string> map = server.getMap();
		std::cout << map["port"] << std::endl;
	}
	catch(const std::exception& e)
	{
	}
	
}