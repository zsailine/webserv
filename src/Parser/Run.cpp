/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Run.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:51:36 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/10 10:52:21 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Run.hpp"
#include "class.hpp"

int	flag = 1;

void	signalHandler( int sigNum )
{
	flag = 0;
	std::cout << std::endl;
	std::cout << GREEN "Websev is quitting..." RESET << std::endl;
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
				this->handleSocket(server, index);
			else
				this->handleClient(fd);
		}
	}
	parse.closeFds();
	close(this->_epoll);
}

void	Run::runEpoll( std::vector<Server> &server )
{
	this->_epoll = epoll_create(true);

	for (size_t i = 0; i < server.size(); i++)
		addEpollEvent(this->_epoll, server[i].getSocket());
}

Run::Run( std::string const &parameter )
	: _client(0), _epoll(-1), _parameter(parameter) {}

void	Run::handleSocket( std::vector<Server> &server, int &index )
{
	int			opt;
	int			client_fd;
	sockaddr_in	client_addr;
	socklen_t	client_len;

	client_len = sizeof(client_addr);
	client_fd = accept(server[index].getSocket(), (sockaddr*)&client_addr, &client_len);
	if (client_fd == -1)
		index = this->_client; // breaks the for loop
	opt = 1;
	setsockopt(client_fd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(int));
	server[index].addClient(client_fd);
	addEpollEvent(this->_epoll, client_fd);
}

void	Run::handleClient( int fd )
{
	Sender		sender;
	char		buffer[1024];
	size_t		count = read(fd, buffer, sizeof(buffer));
	std::string	message(buffer, count);
	
	// std::cout << std::endl << std::endl;
	// std::cout << CYAN "****************************************" RESET << std::endl << std::endl;
	// std::cout << CYAN "Received: " RESET << message;
	// std::cout << CYAN "****************************************" RESET << std::endl;
	
	sender.getMessage(message, fd);
	close(fd);
}
