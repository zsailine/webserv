/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Run.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:51:36 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/17 14:04:29 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Run.hpp"
#include "class.hpp"

int	flag = 1;

void	signalHandler( int sigNum )
{
	flag = 0;
	std::cout << std::endl;
	std::cout << RED "Websev is quitting..." RESET << std::endl;
	(void) sigNum;
}

void	Run::run()
{
	Parser				parse(this->_parameter);
	std::vector<Server>	server = parse.getServer();

	this->runEpoll(server);
	while(flag)
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
				Server tmp;
				for (size_t i = 0; i < server.size(); i++)
				{
					std::vector<int> fds = server[i].getClientFds();
					for (size_t j = 0; j < fds.size(); j++)
					{
						if (fd == fds[j])
						{
							tmp = server[i];
							break;
						}
					}
				}
				this->handleClient(fd, tmp);
			}
		}
	}
	for (size_t i = 0; i < server.size(); i++)
		server[i].closeFds();
	close(this->_epoll);
}

void	Run::runEpoll( std::vector<Server> &server )
{
	this->_epoll = epoll_create(true);
	for (size_t i = 0; i < server.size(); i++)
	{
		std::vector<int> tmp = server[i].getSocket();
		for (size_t u = 0; u < tmp.size(); u++)
			addEpollEvent(this->_epoll, tmp[u]);
	}
}

Run::Run( std::string const &parameter )
	: _client(0), _epoll(-1), _parameter(parameter) {}

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

void	Run::handleClient( int fd , Server server)
{
	Sender		sender;
	char		buffer[1024];
	size_t		count = read(fd, buffer, sizeof(buffer));
	std::string	message(buffer, count);
	
	sender.handleRequest(message, fd, server);
	close(fd);
}
