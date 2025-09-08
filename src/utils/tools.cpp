/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:58:05 by mitandri          #+#    #+#             */
/*   Updated: 2025/09/08 10:18:19 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../Parser/Body.hpp"
#include "../Sender/Response.hpp"
#include "../cgi/CGI.hpp"
#include "../Parser/Run.hpp"
#include "../cgi/CgiReactor.hpp"


class Run;

void	printLogs( string method, string path, string version )
{
	Run		run;
	string	intro;

	if (method == "GET")
		intro = string(CYAN "REQUEST GET\t:\t");
	else if (method == "POST")
		intro = string(GREEN "REQUEST POST\t:\t");
	else if (method == "DELETE")
		intro = string(YELLOW "REQUEST DELETE\t:\t");
	else
		intro = string(RED"REQUEST " + method + "\t:\t");
	addEpollEvent(run.getEpoll(), STDOUT_FILENO);
	std::cout << intro + method + " " + path + " " + version << std::endl;
	std::cout << RESET;
	delEpollEvent(run.getEpoll(), STDOUT_FILENO);
}

void	printAnswer( Body &body, Response &ref )
{
	Run		run;
	string	intro;
	string	color = "";

	if (ref.getStatus() >= 400)
		color = RED;
	else
	{
		if (body.getMethod() == "GET") color = CYAN;
		else if (body.getMethod() == "POST") color = GREEN;
		else if (body.getMethod() == "DELETE") color = YELLOW;
		else { color = RED; }
	}
	if (body.getMethod() == "GET")
		intro = color + string("ANSWER GET\t:\t");
	else if (body.getMethod() == "POST")
		intro = color + string("ANSWER POST\t:\t");
	else if (body.getMethod() == "DELETE")
		intro = color + string("ANSWER DELETE\t:\t");
	else
		intro = color + string("ANSWER " + body.getMethod() + "\t:\t");
	addEpollEvent(run.getEpoll(), STDOUT_FILENO);
	std::cout << intro + body.getVersion() + " " << ref.getStatus()
		<< " " + ref.description(ref.getStatus()) + RESET << std::endl;
	std::cout << RESET;
	delEpollEvent(run.getEpoll(), STDOUT_FILENO);
}

string	readFile( string path )
{
	std::ifstream		file(path.c_str());
	std::stringstream	ss;

	if (file.is_open())
	{
		ss << file.rdbuf();
		file.close();
		return ss.str();
	}
	return "";
}

void	writeFile( string path, string content )
{
	std::ofstream	file(path.c_str());

	if (file.is_open())
	{
		file << content;
		file.close();
	}
}

string	getType( string message, string toFind, string end )
{
	string	temp = message;
	size_t	start = temp.find(toFind), ending;

	if (start == string::npos)
		return "";
	temp = temp.c_str() + start;
	ending = temp.find(end);
	temp = temp.substr(0, ending);
	return temp.c_str() + toFind.size() + 1;
}

string	generateHTML( int status, string description )
{
	string	html;

	if (status == 204)
		return "";
	html.append("<!DOCTYPE html>");
	html.append("<style>.center{text-align: center;}</style>");
	html.append("<html><body>");
	html.append("<h1 style=\"text-align: center;\" >" + toString(status)
		+ " " + description + "</h1>");
	html.append("<div class=\"center\"><a href=\"../index.html\"><- Go back to home page</a></div>");
	html.append("<html><body>");
	return html;
}

bool	fileExist( string path )
{
	struct stat	st;
	
	if (stat(path.c_str(), &st) != 0)
		return false;
	return true;
}

bool	hasPermission( string path, int	mode )
{
	if (access(path.c_str(), mode) != 0)
		return false;
	return true;
}

static bool endsWith(const std::string &s, const char *suf) {
    size_t n = strlen(suf);
    return s.size() >= n && s.compare(s.size()-n, n, suf) == 0;
}

bool isPhpUri(const std::string &uri) {
    if (endsWith(uri, ".php")) return true;
    std::string::size_type pos = uri.find(".php?");
    return (pos != std::string::npos);
}

std::string extractRequestURI(const std::string &header) {
    std::string::size_type eol = header.find("\r\n");
    if (eol == std::string::npos) return "";
    std::string first = header.substr(0, eol);
    std::istringstream iss(first);
    std::string method, uri, version;
    iss >> method >> uri >> version;
    return uri;
}

// Parse basique des headers
void parseHeadersToMap(const std::string &header,
                              std::map<std::string,std::string> &out) {
    out.clear();
    std::string::size_type pos = header.find("\r\n");
    if (pos == std::string::npos) return;
    std::string rest = header.substr(pos + 2);
    while (!rest.empty()) {
        std::string::size_type nl = rest.find("\r\n");
        std::string line = (nl == std::string::npos) ? rest : rest.substr(0, nl);
        if (line.empty()) break;
        std::string::size_type col = line.find(':');
        if (col != std::string::npos) {
            std::string name  = line.substr(0, col);
            std::string value = line.substr(col + 1);
            while (!value.empty() && (value[0]==' ' || value[0]=='\t')) value.erase(0,1);
            out[name] = value;
        }
        if (nl == std::string::npos) break;
        rest = rest.substr(nl + 2);
    }
}

// Résout le chemin disque du script via root + path (sans query)
std::string resolveScriptFilename(const std::string &uri) {
    std::string path = uri;
	std::string::size_type q = path.find('?');
    if (q != std::string::npos) path.erase(q);
    return path;
}

