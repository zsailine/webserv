/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:30:30 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/30 10:49:48 by mitandri         ###   ########.fr       */
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
	
		void	findResource( Server &server, string &key, string &value );
	
	public:

		Delete( string message ) : Post(message) {}
		~Delete() {}
		void	deleteResource( Server &server );
		// void	printMother();
};


#endif
