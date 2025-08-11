/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Run.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:51:36 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/11 09:03:01 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Run.hpp"
#include "class.hpp"

int	flag = 1;
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
	sig = 0;
	std::cout << std::endl;
	std::cout << PURPLE "... Websev is quitting..." RESET << std::endl;
	(void) sigNum;
}

void	Run::run()
{
	Request				req;
	Parser				parse(this->_parameter);
	bool				done = false, sent = false;
	std::vector<Server>	server = parse.getServer();
	
	std::cout << PURPLE "... WELCOME TO OUR WEBSERVER ...\n" RESET;
	this->runEpoll(server);
	while(sig)
	{
		signal(SIGINT, signalHandler);
		this->_client = epoll_wait(this->_epoll, this->_events, MAX_EVENTS, -1);
		for (int i = 0; i < this->_client; i++)
		{
			int fd = this->_events[i].data.fd;
			int index = isSocket(fd, server);
			if (index >= 0)
				this->handleSocket(fd, server, index);
			else
			{
				try { if (this->_events[i].events & EPOLLIN)
				{
					done = this->handleClient(req, server, fd);
					if (done)
						modifyEpollEvent(this->_epoll, fd, EPOLLOUT);
				}
				else if (done && this->_events[i].events & EPOLLOUT)
				{
					sent = req.sendChunks(fd);
					if (sent)
					{
						sent = false; done = false;
						server[i].setfd(fd, -1);
						close(fd);
					}
				} } catch ( const std::exception &e ) { std::cout << e.what() << std::endl; }
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

bool	Run::handleClient( Request &req, std::vector<Server> &server, int &fd )
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
	return req.readChunks(fd, server[i]);
}

void	Run::closeAll( std::vector<Server> &server )
{
	for (size_t i = 0; i < server.size(); i++)
		server[i].closeFds();
	close(this->_epoll);
}
