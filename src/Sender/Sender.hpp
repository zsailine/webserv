/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:19:34 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/10 13:53:51 by mitandri         ###   ########.fr       */
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

		int			_status;
		std::string	_description;
		std::string	_response;

	public:

		Sender() {}
		int		getStatus() const;
		void	getMessage( std::string message, int fd );
		void	sendMessage( int fd );
		void	defineStatus();
		void	getResponse( ServerResponse &ref );
		void	postResponse( std::string &message, ServerResponse &ref );
};

#endif
