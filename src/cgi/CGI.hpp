#pragma once
#include "lib.hpp"
#include "class.hpp"

class CGI {
public:
    void    setMethod(const std::string& m) { _method = m; }
    void    setBody(const std::string& b)   { _body = b; }
    void    setRequestURI(const std::string& s)   { _request_uri = s; }
    void    setScriptFilename(const std::string& s){ _script_path = s; }
    void    setScriptName(const std::string& s)   { _script_name = s; }
    void    setServerName(const std::string& s)   { _server_name = s; }
    void    setServerPort(const std::string& s)   { _server_port = s; }
    void    setRemoteAddr(const std::string& s)   { _remote_addr = s; }
    void    setRemotePort(const std::string& s)   { _remote_port = s; }
    void    setDocumentRoot(const std::string& s) { _document_root = s; }
    void    setHeader(const std::string& k, const std::string& v) { _headers[k] = v; }
    bool    start_cgi(int epfd, int client_fd);
    void    retrieve_query_string();
    char**  generate_envp();

private:
    std::string _method;
    std::string _body;

    std::string _request_uri;   
    std::string _script_path;   
    std::string _script_name;   
    std::string _query_string;

    std::string _server_name;   
    std::string _server_port;   
    std::string _remote_addr;   
    std::string _remote_port;   
    std::string _document_root; 

    std::map<std::string, std::string> _headers;
};
