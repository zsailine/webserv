/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Store.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:15:29 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/09 15:41:28 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Store.hpp"

void	Store::storeData( string &message )
{
	int		index = message.rfind('\n');
	string	data = message.c_str() + index + 1;
	int		count = std::count(data.begin(), data.end(), '&');

	for (int i = 0; i < (count + 1); i++)
	{
		int	j = data.find('&');
		string	temp = data.substr(0, j);
		
		data = data.substr(j + 1, data.size() - j);
	}
}
