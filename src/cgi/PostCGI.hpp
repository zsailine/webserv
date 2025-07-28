#ifndef POST_CGI
#define POST_CGI

#include "lib.hpp"
#include "class.hpp"

class CGI;

class PostCgi
{
private:
	std::string _message;
	std::string _body;
	std::string _contentType;
	size_t _contentLength;

public:
	PostCgi(const std::string& rawRequest);
	void parseBody();
	void extractContentType();
	void applyToCgi(CGI& cgi);
    ~PostCgi(){};
};


#endif