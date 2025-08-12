/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:12:07 by aranaivo          #+#    #+#             */
/*   Updated: 2025/08/11 13:20:27 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./CGI.hpp"

CGI::CGI(std::string message, std::string path, std::string method, int client_fd)
{
    _path = path;
    _method = method;
    _client_fd = client_fd;
    _message = message;
}

void CGI::execute_cgi()
{
    int stdout_pipe[2];
    pipe(stdout_pipe);

    int stdin_pipe[2];
    if (_method == "POST")
        pipe(stdin_pipe);

    pid_t pid = fork();
    if (pid == 0)
    {
        // === Processus fils ===

        // Redirection STDOUT → stdout_pipe[1]
        close(stdout_pipe[0]);
        dup2(stdout_pipe[1], STDOUT_FILENO);
        close(stdout_pipe[1]);

        // Redirection STDIN si POST
        if (_method == "POST")
        {
            close(stdin_pipe[1]);
            dup2(stdin_pipe[0], STDIN_FILENO);
            close(stdin_pipe[0]);
        }

        // Récupérer les variables d'environnement
        this->retrieve_query_string();
        char** envp = this->generate_envp();

        const char* php_path = "/usr/bin/php-cgi";
        char* argv[] = { (char*)"php-cgi", NULL };

        execve(php_path, argv, envp);

        // Si execve échoue :
        perror("execve failed");
        exit(1);
    }
    else
    {
        // === Processus père ===

        // Fermeture des extrémités inutiles
        close(stdout_pipe[1]);
        if (_method == "POST")
        {
            close(stdin_pipe[0]);
            write(stdin_pipe[1], _body.c_str(), _body.size()); // Envoie du body POST
            close(stdin_pipe[1]);
        }

        // Lecture de la sortie CGI
        std::string response;
        char buffer[4096];
        ssize_t count;

        while ((count = read(stdout_pipe[0], buffer, sizeof(buffer))) > 0)
        {
            response.append(buffer, count);
        }

        close(stdout_pipe[0]);
        waitpid(pid, NULL, 0);

        // Envoie de la réponse au client (préfixée d'une ligne de statut HTTP)
        write(_client_fd, "HTTP/1.1 200 OK\r\n", 17);
        write(_client_fd, response.c_str(), response.size());

        _response = response; // Pour log ou debug
    }
}


void CGI::retrieve_query_string()
{
    size_t question_mark = _path.find('?');

    if (question_mark != std::string::npos)
    {
        _path = _path.substr(0, question_mark);
        _query_string = _path.substr(question_mark + 1);
    }
    else
    {
        _query_string = "";
    }
}

void CGI::handle_post()
{

}

std::string to_string(int value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

char ** CGI::generate_envp()
{
    std::vector<std::string> env_strings;
    char buf[1024];
    std::string script_path;

    if (getcwd(buf, sizeof(buf)) == NULL)
    {
        std::cout << "An error has occured on path " << std::endl;
        return NULL;
    }

    script_path = std::string(buf) + "/www/website1/cgi" + _path;

    if (access(script_path.c_str(), F_OK) != 0) 
    {
        std::cerr << "PHP script not found at: " << script_path << std::endl;
    }

    env_strings.push_back("REDIRECT_STATUS=200");
    env_strings.push_back("REQUEST_METHOD=" + _method);
    env_strings.push_back("SCRIPT_FILENAME=" + script_path);
    env_strings.push_back("QUERY_STRING=" + _query_string);
    env_strings.push_back("GATEWAY_INTERFACE=CGI/1.1");
    env_strings.push_back("SERVER_PROTOCOL=HTTP/1.1");
    env_strings.push_back("SERVER_SOFTWARE=MiniCPPServer/1.0");
    env_strings.push_back("REMOTE_ADDR=127.0.0.1");

    if (_method == "POST")
    {
        env_strings.push_back("CONTENT_TYPE=" + _content_type);   // exemple : application/x-www-form-urlencoded
        env_strings.push_back("CONTENT_LENGTH=" + to_string(_content_length));
    }

    char **envp = (char **)malloc(sizeof(char *) * (env_strings.size() + 1));
    if (!envp)
        return NULL;

    for (size_t i = 0; i < env_strings.size(); ++i)
    {
        envp[i] = strdup(env_strings[i].c_str());
    }

    envp[env_strings.size()] = NULL;

    return envp;
}


std::string CGI::getResponse()
{
    return (_response);
}

void CGI::setBody(std::string body)
{
    _body = body;
}

void CGI::setContentType(std::string content_type)
{
    _content_type = content_type;
}

void CGI::setContentLength(size_t content_length)
{
    _content_length = content_length;
}

CGI::~CGI()
{}