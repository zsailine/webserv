/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiJob.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:34:57 by zsailine          #+#    #+#             */
/*   Updated: 2025/08/26 15:35:52 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <sys/types.h>

class CgiJob {
public:
    int          client_fd;
    pid_t        pid;
    int          cgi_out;      
    int          cgi_in;       
    std::string  in_buf;       
    size_t       in_off;       
    std::string  out_buf;      

    // HTTP final
    bool         headers_done;
    int          status_code;
    std::string  http_headers;
    std::string  http_body;

    // signalisation
    bool         child_exited;

    CgiJob()
    : client_fd(-1), pid(-1), cgi_out(-1), cgi_in(-1),
      in_off(0), headers_done(false), status_code(200),
      child_exited(false) {}
};
