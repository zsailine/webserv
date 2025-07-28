
#include "./PostCGI.hpp"

PostCgi::PostCgi(const std::string& rawRequest)
{
    _message = rawRequest;
    parseBody();
    extractContentType();
    _contentLength = _body.length();
}

void PostCgi::parseBody()
{
    size_t start = _message.find("\r\n\r\n");
    if (start != std::string::npos)
        _body = _message.substr(start + 4);
}

void PostCgi::extractContentType()
{
    Tools tools;
    _contentType = tools.getType(_message, "Content-Type:", "\r\n");
    if (_contentType.empty())
        _contentType = "application/x-www-form-urlencoded"; // valeur par défaut
}

void PostCgi::applyToCgi(CGI& cgi)
{
    cgi.setBody(_body);
    cgi.setContentType(_contentType);
    cgi.setContentLength(_contentLength);
}
