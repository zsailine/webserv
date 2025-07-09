/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:09 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/09 15:08:53 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_RESPONSE_HPP
#define SERVER_RESPONSE_HPP

#include "lib.hpp"
#include "class.hpp"

class ServerResponse
{
    private:
    
        std::string                         _path;
        std::string                         _content;
        std::string                         _mime;
        std::string                         _response;
        std::string                         _version;
        std::string                         _method;
        std::string                         _message;
        std::map<std::string, std::string>  _mimetype;

    public:
    
        ServerResponse( std::string const &message );

        void        get_full_path(const std::string &req);
        std::string get_file_content( std::string path );
        void        getExtension();
        void        run();

        std::string getPath() const;
        std::string getContent() const;
        std::string getMime() const;
        std::string getResponse() const;
        std::string getVersion() const;
        std::string getMethod() const;

        ~ServerResponse();
};

#endif