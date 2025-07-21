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
        // Processus fils
        close(pipefd[0]); // Ferme lecture

        dup2(pipefd[1], STDOUT_FILENO); // Redirige stdout vers pipe
        close(pipefd[1]);

        // Recuperer le query string
        this->retrieve_query_string();
        
        // Genrere le env de execve;
        envp = this->generate_envp();

        // // Variables d'environnement
        // setenv("REDIRECT_STATUS", "200", 1);
        // setenv("SCRIPT_FILENAME", _path.c_str(), 1);
        // setenv("REQUEST_METHOD", _method.c_str(), 1);
        // setenv("QUERY_STRING", _query_string.c_str(), 1);

        // if (_method == "POST")
        // {
        //     char content_length[20];
        //     sprintf(content_length, "%lu", _body.length());
        //     setenv("CONTENT_LENGTH", content_length, 1);
        //     setenv("CONTENT_TYPE", "application/x-www-form-urlencoded", 1);

        //     // Redirige stdin pour envoyer le body à php-cgi
        //     int post_pipe[2];
        //     pipe(post_pipe);
        //     pid_t post_pid = fork();
        //     if (post_pid == 0)
        //     {
        //         // Petit-fils : écrit le body dans stdin du php-cgi
        //         close(post_pipe[0]);
        //         write(post_pipe[1], _body.c_str(), _body.length());
        //         close(post_pipe[1]);
        //         exit(0);
        //     }
        //     else
        //     {
        //         // Fils : lit depuis post_pipe[0] et l'assigne à stdin
        //         close(post_pipe[1]);
        //         dup2(post_pipe[0], STDIN_FILENO);
        //         close(post_pipe[0]);
        //     }
        // }

        execlp("php-cgi", "php-cgi", NULL);

        // Si execlp échoue
        perror("execlp failed");
        exit(1);
    }
    else
    {
        // Processus père : récupère la réponse et l'envoie au client
        close(pipefd[1]); // Ferme écriture

        char buffer[4096];
        ssize_t count;
        while ((count = read(pipefd[0], buffer, sizeof(buffer))) > 0)
        {
            write(_client_fd, buffer, count);
        }

        close(pipefd[0]);
        waitpid(pid, NULL, 0);
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

    env_strings.push_back("REDIRECT_STATUS=200");
    env_strings.push_back("REQUEST_METHOD=" + _method);
    env_strings.push_back("SCRIPT_FILENAME=" + _path);
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

CGI::~CGI()
{}