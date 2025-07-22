/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:08:49 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/21 10:51:40 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "class.hpp"
#include "lib.hpp"

class CGI
{
    private:
        std::string _path;
        std::string _query_string;
        std::string _method;
        std::string _body;
        std::string _response;
        int         _client_fd;

    public:
        CGI(std::string path, std::string method, int client_fd);
        void retrieve_body();
        void retrieve_query_string();
        void handle_post();
        void execute_cgi();
        char **generate_envp();
        std::string getResponse();
        ~CGI();
};




#endif