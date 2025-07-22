/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:12:07 by aranaivo          #+#    #+#             */
/*   Updated: 2025/07/21 10:57:58 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./CGI.hpp"

CGI::CGI(std::string path, std::string method, int client_fd)
{
    _path = path;
    _method = method;
    _client_fd = client_fd;
}

void CGI::execute_cgi()
{
    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();
    if (pid == 0)
    {
        char **envp;

        // Recuperer le query string
        this->retrieve_query_string();
        
        // Genrere le env de execve;
        envp = this->generate_envp();
        close(pipefd[0]); // Ferme lecture

        dup2(pipefd[1], STDOUT_FILENO); // Redirige stdout vers pipe
        close(pipefd[1]);


        const char *php_path = "/usr/bin/php-cgi";
        char *argv[] = { (char*)"php-cgi", NULL };

        execve(php_path, argv, envp);
        exit(1);
    }
    else
    {
        close(pipefd[1]); // Ferme écriture dans le père

        std::string response; // pour stocker toute la réponse
        std::string content_length;
        char buffer[4096];
        ssize_t count;

        while ((count = read(pipefd[0], buffer, sizeof(buffer))) > 0)
        {
            response.append(buffer, count);
        }
        // Écrire la ligne de statut HTTP
        content_length = "Content-Length: " + response.size();
        write(_client_fd, "HTTP/1.1 200 OK\r\n", 17);
        write(_client_fd, response.c_str(), response.size());
        

        close(pipefd[0]);
        waitpid(pid, NULL, 0);

        _response = response; // 
    }
}

void CGI::retrieve_body()
{

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

CGI::~CGI()
{}