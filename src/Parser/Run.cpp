/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Run.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:51:36 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/26 09:37:57 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Run.hpp"
#include "class.hpp"

int	sig = 1;
int	Run::_epoll;

int isSocket(int fd, std::vector<Server> server)
{
	for (size_t i = 0; i < server.size(); i++)
	{
		if (std::find(server[i].getSocket().begin(),
			server[i].getSocket().end(), fd) != server[i].getSocket().end())
			return (server[i].getIndex());
	}
	return (-1);
}

void	signalHandler( int sigNum )
{
	Run	run;
	
	sig = 0;
	addEpollEvent(run.getEpoll(), STDOUT_FILENO);
	std::cout << std::endl;
	std::cout << PURPLE "... Webserv is quitting..." RESET << std::endl;
	delEpollEvent(run.getEpoll(), STDOUT_FILENO);
	(void) sigNum;
}

static void	printInstruction( std::vector<Server> &server )
{
	std::cout << PURPLE "... WELCOME TO OUR WEBSERVER ...\n" RESET << std::endl;
	std::cout << "Press (Ctrl + C) to stop the server" << std::endl << std::endl;
	for (size_t i = 0; i < server.size(); i++)
	{
		string	port = server[i].get("listen");
		int		index = port.find(":");
		port = port.substr(index + 1, string::npos);
		std::cout << "Server " << i + 1 << " [" UNDERLINE << server[i].get("server_name")
			<< RESET "] listening on port " UNDERLINE << port << RESET << std::endl; 
	}
	std::cout << std::endl;
}

void	Run::run()
{
	int					indie;
	Request				req;
	Parser				parse(this->_parameter);
	bool				done = false, sent = false;
	std::vector<Server>	server = parse.getServer();
	
	printInstruction(server);
	this->runEpoll(server);
	while(sig)
	{
		signal(SIGINT, signalHandler);
		this->_client = epoll_wait(this->_epoll, this->_events, MAX_EVENTS, -1);
		for (int i = 0; i < this->_client; i++)
		{
			int fd = this->_events[i].data.fd;
			CgiReactor::instance().debugPrintJobs();
			if (CgiReactor::instance().isCgiFd(fd)) 
			{
                CgiReactor::instance().handleIoEvent(this->_epoll, fd, this->_events[i].events, req);
                continue; // on a géré cet event
            }
			int index = isSocket(fd, server);
			if (index >= 0)
				this->handleSocket(fd, server, index);
			else
			{
				try { if (this->_events[i].events & EPOLLIN)
				{
					try 
					{ 
						done = this->handleClient(req, server, fd, indie); 
					}
					catch ( const std::exception &e ) { done = true; }
					if (done)
					{
						done = false;
						modifyEpollEvent(this->_epoll, fd, EPOLLOUT);
					}
				}
				else if (	this->_events[i].events & EPOLLOUT)
				{
					sent = req.sendChunks(fd, server[indie]);
					if (sent)
					{
						sent = false;
						server[indie].setfd(fd, -1);
						close(fd);
					}
				} } catch ( const std::exception &e ) {
					addEpollEvent(this->_epoll, STDOUT_FILENO);
					std::cout << e.what() << std::endl;
					delEpollEvent(this->_epoll, STDOUT_FILENO); }
			}
		}
	}
	this->closeAll(server);
}

static void	closeFds( std::vector<Server> &server )
{
	for (size_t i = 0; i < server.size(); i++)
	{
		server[i].closeFds();
	}
	throw std::exception();
}

void	Run::runEpoll( std::vector<Server> &server )
{
	this->_epoll = epoll_create(true);
	for (size_t i = 0; i < server.size(); i++)
	{
		server[i].setEpFd(this->_epoll);
		std::vector<int> tmp = server[i].getSocket();
		for (size_t u = 0; u < tmp.size(); u++)
		{
			addEpollEvent(this->_epoll, tmp[u]);
			if (listen(tmp[u], 2) != 0)
			{
				std::cerr << "Error listening socket for Server "
					<< server[i].getIndex() << std::endl; 
				closeFds(server);
			}
		}
	}
	addEpollEvent(this->_epoll, STDIN_FILENO);
	addEpollEvent(this->_epoll, STDERR_FILENO);
	addEpollEvent(this->_epoll, STDOUT_FILENO);
}

Run::Run( std::string const &parameter )
	: _client(0), _parameter(parameter) {}

void	Run::handleSocket( int fd, std::vector<Server> &server, int &index )
{
	int			opt;
	int			client_fd;
	sockaddr_in	client_addr;
	socklen_t	client_len;

	client_len = sizeof(client_addr);
	client_fd = accept(fd, (sockaddr*)&client_addr, &client_len);
	if (client_fd == -1)
		index = this->_client; // breaks the for loop
	opt = 1;
	setsockopt(client_fd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(int));
	server[index].addClient(client_fd);
	addEpollEvent(this->_epoll, client_fd);
}

bool	Run::handleClient( Request &req, std::vector<Server> &server, int &fd, int &index )
{
	size_t		i = 0;
	int			flag = 1;
	
	while (i < server.size() && flag)
	{
		std::vector<int> fds = server[i].getClientFds();
		for (size_t j = 0; j < fds.size(); j++)
		{
			if (fd == fds[j])
			{
				flag = 0;
				break ;
			}
		}
		if (flag)
			i++;
	}
	index = i;
	return req.readChunks(fd, server[i]);
}

void	Run::closeAll( std::vector<Server> &server )
{
	for (size_t i = 0; i < server.size(); i++)
		server[i].closeFds();
	close(this->_epoll);
}
