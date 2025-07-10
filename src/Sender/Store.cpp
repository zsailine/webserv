/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Store.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:15:29 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/10 13:56:46 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Store.hpp"

int					_already = 0;
std::string			_value = "";
std::vector<string>	Store::_storer;

void	Store::storeData( string &message )
{
	int		index = message.rfind('\n');
	string	data = message.c_str() + index + 1;
	string	value;

	value = data.c_str() + data.find('=') + 1;
	if (std::find(this->_storer.begin(), this->_storer.end(), value) != this->_storer.end())
		_already = 1;
	else
	{
		_already = 0;
		this->_storer.push_back(value);
	}
	_value = value;
}

void	Store::printStorer() const
{
	for (auto it = this->_storer.begin(); it != this->_storer.end(); ++it)
		std::cout << "[" << *it << "]" << std::endl;
}

void	Store::sendAnswer( int &status, string &description, ServerResponse &ref )
{
	std::ostringstream	response;

	if (_already)
		this->generateAlready();
	else
		this->generateNew();
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
	this->_http.append("<p style=\"text-align: center;\" >"
		+ _value + " is already there </p>");
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
	this->_http.append("<p style=\"text-align: center;\" > Welcome "
		+ _value + "</p>");
	this->_http.append("<div class=\"center\"><a href=\""
		+ this->_path + "\"><- Go back to home page</a></div>");
	this->_http.append("</body>");
	this->_http.append("</html>");
}

std::string Store::getHttp() const { return this->_http; }

std::string	Store::getAnswer() const { return this->_answer; }

std::string	Store::getPath() const { return this->_path; }

void	Store::setPath( string path )
{
	this->_path = path;
}
