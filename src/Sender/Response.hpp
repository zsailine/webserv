/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:09 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/30 11:08:07 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_RESPONSE_HPP
#define SERVER_RESPONSE_HPP

#include "lib.hpp"
#include "class.hpp"

class Tools;

class Response
{
    private:
    
        int                                  _status;
        string                               _path;
        string                               _content;
        string                               _mime;
        string                               _response;
        string                               _version;
        string                               _method;
        string                               _message;
        std::map<std::string, std::string>  _mimetype;

    public:
    
        Response( std::string const &message );

        void        set_header(const std::string &req);
        void        defineStatus();
        void        getExtension();
        void        set_path(std::string index, std::string url, std::string path);
        void        http( int status, string file );
        string      description ( int status );
        void        run();

        string      getPath() const { return this->_path; }
        string      getContent() const { return this->_content; } 
        string      getMime() const { return this->_mime; }
        string      getResponse() const { return this->_response; } 
        string      getVersion() const { return this->_version; } 
        string      getMethod() const { return this->_method; }
        int         getStatus() const { return this->_status; }

        void        set_status( int status ) { this->_status = status; }
        void        set_path( std::string path ) { this->_path = path; }

        ~Response() {}
};

#endif