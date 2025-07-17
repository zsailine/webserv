/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:09 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/17 12:56:39 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_RESPONSE_HPP
#define SERVER_RESPONSE_HPP

#include "lib.hpp"
#include "class.hpp"

class ServerResponse
{
    private:
    
        std::string                         _buffer;
        std::string                         _path;
        std::string                         _content;
        std::string                         _mime;
        std::string                         _method;
        std::string                         _response;
        std::map<std::string, std::string>  _mimetype;
        ServerResponse(/* args */);
    
    public:
    
        ServerResponse(std::string _buffer);
        ServerResponse(ServerResponse const &toCopy);
        void    set_header(const std::string &req);
        void    get_file_content();
        void    get_mime_type();
        void    make_Http_response(int status);
        void    run();

        std::string get_path();
        std::string get_content();
        std::string get_mime();
        std::string get_response();
        std::string get_method();
        void set_path(std::string index,std::string url, std::string path);

        ~ServerResponse();
};

#endif