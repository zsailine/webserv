/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:09 by aranaivo          #+#    #+#             */
/*   Updated: 2025/08/11 09:06:06 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_RESPONSE_HPP
#define SERVER_RESPONSE_HPP

#include "lib.hpp"
#include "../Parser/Body.hpp"
#include "../utils/utils.hpp"

class Response
{
    private:
        int                                  _status;
        string                               _path;
        string                               _mime;
        string                               _response;
        std::map<std::string, std::string>  _mimetype;

    public:
        Response();
        void        defineStatus();
        void        getExtension();
        void        set_path(std::string index, std::string url, std::string path);
        void        http( Body bod, string file );
        string      description ( int status );

        string      getPath() const { return this->_path; }
        string      getMime() const { return this->_mime; }
        string      getResponse() const { return this->_response; } 
        int         getStatus() const { return this->_status; }

        void        set_status( int status ) { this->_status = status; }
        void        set_path( std::string path ) { this->_path = path; }

        ~Response() {}
};

#endif