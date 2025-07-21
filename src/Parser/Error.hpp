/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsailine < zsailine@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:56:33 by zsailine          #+#    #+#             */
/*   Updated: 2025/07/21 14:27:32 by zsailine         ###   ########.fr       */
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