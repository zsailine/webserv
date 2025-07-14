/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Store.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:15:29 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/14 16:02:13 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Store.hpp"

std::vector<string>	Store::_simple;

void	Store::parsePost( string &message )
{
	if (message.find("boundary=") == string::npos)
		this->parseSimple(message);
	else
	{
		int		index = message.find("boundary=");
		string	boundary = message.c_str() + index;
		boundary = boundary.substr(boundary.find('=') + 1, boundary.find('\r'));
		this->parseComplex(message, boundary);
	}
}

void	Store::printStorer() const
{
	for (auto it = this->_simple.begin(); it != this->_simple.end(); ++it)
		std::cout << "[" << *it << "]" << std::endl;
}

void	Store::sendAnswer( int &status, string &description, ServerResponse &ref )
{
	std::ostringstream	response;

	// if (_already)
	// 	this->generateAlready();
	// else
	// 	this->generateNew();
	response << ref.getVersion() << " "
		<< status << " " << description << "\r\n"
		<< "Content-Type: text/html" << "\r\n"
		<< "Content-Length: " << this->getHttp().size() << "\r\n"
		<< "\r\n" << this->_http;
	this->_answer = response.str();
}

void	Store::generateAlready()
{
	this->_http.append("<!DOCTYPE html>");
	this->_http.append("<style>.center{text-align: center;}</style>");
	this->_http.append("<html>");
	this->_http.append("<body>");
	this->_http.append("<h1 style=\"text-align: center;\" > Sent ! </h1>");
	this->_http.append("<p style=\"text-align: center;\" > is already there </p>");
	this->_http.append("<div class=\"center\"><a href=\""
		+ this->_path + "\"><- Go back to home page</a></div>");
	this->_http.append("</body>");
	this->_http.append("</html>");
}

void	Store::generateNew()
{
	this->_http.append("<!DOCTYPE html>");
	this->_http.append("<style>.center{text-align: center;}</style>");
	this->_http.append("<html>");
	this->_http.append("<body>");
	this->_http.append("<h1 style=\"text-align: center;\" > Sent ! </h1>");
	this->_http.append("<p style=\"text-align: center;\" > Welcome </p>");
	this->_http.append("<div class=\"center\"><a href=\""
		+ this->_path + "\"><- Go back to home page</a></div>");
	this->_http.append("</body>");
	this->_http.append("</html>");
}

void	Store::parseSimple( string &message )
{
	int		index = message.rfind("\n");
	string	data = message.c_str() + index + 1;
	int		count = std::count(data.begin(), data.end(), '&');

	this->_type = "simple";
	for (int i = 0; i <= count; i++)
	{
		index = data.find('&');
		if ((unsigned long)index == string::npos)
			index = (int)data.size();
		this->_simple.push_back(data.substr(0, index));
		if (index != (int)data.size())
			data = data.substr(index + 1, data.size());
	}
	this->printStorer();
}

void	Store::parseComplex( string &message, string &sep )
{
	(void)message;
	(void)sep;
}

std::string Store::getHttp() const { return this->_http; }

std::string	Store::getAnswer() const { return this->_answer; }

std::string	Store::getPath() const { return this->_path; }

void	Store::setPath( string path )
{
	this->_path = path;
}
