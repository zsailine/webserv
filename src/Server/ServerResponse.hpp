/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:09 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/04 12:49:57 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_RESPONSE_HPP
#define SERVER_RESPONSE_HPP


#include "../../lib/lib.hpp"
#include "../../src/utils/utils.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

class ServerResponse
{
    private:
        std::string _buffer;
        std::string _path;
        std::string _content;
        std::string _mime;
        std::string _response;
    
    public:
        ServerResponse(/* args */);
        ServerResponse(std::string _buffer);
        ServerResponse(ServerResponse &obj);
        ServerResponse & operator=(ServerResponse &obj);

        void get_full_path(const std::string &req);
        void get_file_content();
        void get_mime_type();
        void make_Http_response(int status);

        std::string get_path();
        std::string get_content();
        std::string get_mime();
        std::string get_response();

        ~ServerResponse();
};

#endif