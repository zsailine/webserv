/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:45:20 by mitandri          #+#    #+#             */
/*   Updated: 2025/06/27 16:00:36 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Server/define.hpp"

class	Client
{
	private:

		int		_socket;

	public:

		Client();
		~Client();

		int		getSocket() const;
};

#endif
