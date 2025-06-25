/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:17:07 by aranaivo          #+#    #+#             */
/*   Updated: 2025/06/24 14:16:10 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cstring>         
#include <netdb.h>
#include <cstring>         // memset
#include <arpa/inet.h>     // inet_ntop
#include <netinet/in.h>    // sockaddr_in
#include <iostream>
#include <sstream>

int stringToInt(std::string& str) {
    std::stringstream ss(str);
    int result;
    ss >> result;
    return result;
}

int get_port_value(std::string port_str)
{
    if (stringToInt(port_str) > 65534)
        throw std::exception();
    return (stringToInt(port_str));
}

in_addr get_resolve_ip(std::string &hostname)
{
	struct addrinfo hints, *res;

	std::memset(&hints, 0 , sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int status = getaddrinfo(hostname.c_str(), NULL, &hints, &res);
	if (status != 0) {
        std::cerr << "Erreur getaddrinfo pour " << hostname << " : " << gai_strerror(status) << std::endl;
        exit(1);
    }

	struct sockaddr_in* ipv4 = (struct sockaddr_in*)res->ai_addr;
    struct in_addr ip = ipv4->sin_addr;

    freeaddrinfo(res);
    return (ip);
}

