/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:09 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/08 11:30:40 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_RESPONSE_HPP
#define SERVER_RESPONSE_HPP

#include "lib.hpp"
#include "class.hpp"

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