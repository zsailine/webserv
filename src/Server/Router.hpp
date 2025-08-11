/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:22:07 by zsailine          #+#    #+#             */
/*   Updated: 2025/08/04 14:18:27 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTER_HPP

#define ROUTER_HPP

#include "Server.hpp"
#include "../utils/utils.hpp"

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
				std::string getValue(std::string key);
				std::map<std::string , std::string> getMap() const;
};

#endif