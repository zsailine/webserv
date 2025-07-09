/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Store.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:11:53 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/09 15:26:37 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STORE_HPP
#define STORE_HPP

#include "lib.hpp"
#include "class.hpp"

class Store
{
	private:

		static std::multimap<string, string>	_storer;
		
	public:

		Store() {}
		~Store() {}
		void	storeData( string &message );
};

#endif
