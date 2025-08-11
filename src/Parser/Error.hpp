/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:56:33 by zsailine          #+#    #+#             */
/*   Updated: 2025/08/11 09:01:59 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2025/08/04 14:22:51 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP

#define ERROR_HPP

#include "lib.hpp"
#include "../utils/utils.hpp"

class Error
{
		private:
				std::map<int , std::string> _map;
				void	init_value();
				void	change_value(int &key, std::string &value);
				int		get_type(std::string str, int &type, std::string &value);
				void	check_value();
				
		public:
				Error();
		 		Error(std::vector<std::string> blocks);
				Error(const Error &toCopy);
				~Error(){}
				std::string getError(int key);
				std::map<int , std::string> getMap() const;
				Error	&operator=(const Error &toCopy);
};
#endif
