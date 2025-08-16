/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:09 by aranaivo          #+#    #+#             */
/*   Updated: 2025/08/14 15:07:12 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "lib.hpp"
#include "../Parser/Body.hpp"
#include "../utils/utils.hpp"

class Response
{
    private:
        int                                 _status;
        string                              _path;
        string                              _mime;
        string                              _response;
        string                              _header;
        string                              _body;
        std::map<std::string, std::string>  _mimetype;

    public:
        Response();
        void        defineStatus();
        void        getExtension();
        void        set_path(std::string index, std::string url, std::string path);
        void        http( Body bod);
        void	    generateHeader( Body bod );
        void        pushNewHeader( string header );
        void        response();
        string      description ( int status );

        string      getPath() const { return this->_path; }
        string      getMime() const { return this->_mime; }
        string      getResponse() const { return this->_response; } 
        int         getStatus() const { return this->_status; }

        void        set_status( int status ) { this->_status = status; }
        void        set_path( std::string path ) { this->_path = path; }
        void        set_body( string body ) { this->_body = body; }
        void        set_mime( string mime ) { this->_mime = mime; }

        ~Response() {}
};

#endif