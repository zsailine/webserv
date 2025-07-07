/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:22:07 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/07 15:19:48 by zsailine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTER_HPP

#define ROUTER_HPP

#include "Server.hpp"

class Router
{
		private:
				std::map<std::string , std::string> _map;
				void	init_value();
				void	change_value(std::string const &name, std::string &key, std::string &value);
				int		get_type(std::string const &name, std::string str, std::string &type, std::string &value);
				void	check_value(std::string const &name);
				Router(){}
				
		 public:
		 		Router(std::string const &name, std::vector<std::string> blocks);
				Router(const Router &toCopy);
				~Router(){}

				std::map<std::string , std::string> getMap() const;
};

#endif