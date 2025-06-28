/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:45:20 by mitandri          #+#    #+#             */
/*   Updated: 2025/06/28 18:30:03 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Server/define.hpp"

class	Client
{
	private:

		int					_socket;
		struct sockaddr_in	_identity;

	public:

		Client();
		~Client();

		int		getSocket() const;
		
		// start and init the socket in client
		void	startSocket();
};

#endif
