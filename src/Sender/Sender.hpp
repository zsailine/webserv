/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:19:34 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/17 10:29:14 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENDER_HPP
#define SENDER_HPP

#include "lib.hpp"
#include "class.hpp"

class ServerResponse;

class Sender
{
	private:

		int	_status;
		void	handleGet(int fd, Server &Server, ServerResponse &response);

	public:

		Sender() {}
		int		getStatus() const;
		void	handleRequest( std::string message, int fd, Server &server );
		void	httpResponse();
};

#endif
