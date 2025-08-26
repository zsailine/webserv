/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:19:34 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/26 09:40:56 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENDER_HPP
#define SENDER_HPP

#include "lib.hpp"
#include "class.hpp"

class Response;

class Sender
{
	private:

		std::string	_response;

	public:

		Sender() {}
		void	handleGet( Server &server, Response &response, Body &body );
		void	postResponse( Response &response, Body &body, Server &server );
		void	deleteResponse( Response &response, Body &body, Server &server );
};

#endif
