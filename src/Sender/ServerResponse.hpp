/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:09 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/08 16:26:14 by mitandri         ###   ########.fr       */
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
        std::map<std::string, std::string>  _mimetype;

    public:
    
        ServerResponse();

        void    get_full_path(const std::string &req);
        void    get_file_content();
        void    getExtension();
        void    make_Http_response(int status);
        void    run();

        std::string getPath() const;
        std::string getContent() const;
        std::string getMime() const;
        std::string getResponse() const;
        std::string getVersion() const;
        std::string getMethod() const;

        ~ServerResponse();
};

#endif