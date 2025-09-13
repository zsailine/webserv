/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:09 by aranaivo          #+#    #+#             */
/*   Updated: 2025/09/12 15:22:45 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "lib.hpp"
#include "../Parser/Body.hpp"
#include "../utils/utils.hpp"
#include "../Server/Server.hpp"

struct ResponseData {
    std::string   path;
    std::string header;
    std::vector<char> buffer;
    size_t offset;
    bool header_sent;
    bool opened;
    size_t file_size;
    size_t sent;
    std::string response;
    bool done;
};

class Response
{
    private:
        int                                 _status;
        string                              _path;
        string                              _mime;
        ResponseData                        _response;
        string                              _header;
        string                              _body;
        std::map<std::string, std::string>  _mimetype;

    public:
        Response();
        void        defineStatus();
        void        getExtension();
        void        set_path(std::string index, std::string url, std::string path, int listing);
        void        http( Body &bod);
        void        makeRedirection(std::string redirection);
        void        makeListing(std::string url, Body &bod, Server &server);
        void	    generateHeader( Body &bod );
        void        pushNewHeader( string header );
        void        response();
        string      description ( int status );

        string      getPath() const { return this->_path; }
        string      getMime() const { return this->_mime; }
        ResponseData      &getResponse() { return this->_response; } 
        int         getStatus() const { return this->_status; }

        void        set_status( int status ) { this->_status = status; }
        void        set_path( std::string path ) { this->_path = path; }
        void        set_body( string body ) { this->_body = body; }
        void        set_mime( string mime ) { this->_mime = mime; }

        ~Response() {}
};

#endif