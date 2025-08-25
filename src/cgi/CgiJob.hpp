#pragma once
#include <string>
#include <sys/types.h>

class CgiJob {
public:
    int          client_fd;
    pid_t        pid;
    int          cgi_out;      // lecture (stdout du CGI)
    int          cgi_in;       // écriture (stdin du CGI), -1 si GET
    std::string  in_buf;       // body POST
    size_t       in_off;       // offset écrit
    std::string  out_buf;      // sortie brute CGI (headers CGI + body)

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
