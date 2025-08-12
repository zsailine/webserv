/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:30:30 by mitandri          #+#    #+#             */
/*   Updated: 2025/08/08 13:51:58 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETE_HPP
#define DELETE_HPP

#include "lib.hpp"
#include "Post.hpp"
#include "../Server/Server.hpp"

class Delete : public Post
{
	private:
	
		void	findResource( string host, string &key, string &value );
	
	public:

		Delete() : Post() {}
		~Delete() {}
		void	deleteResource( string host, string header );
};


#endif
