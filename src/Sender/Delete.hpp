/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:30:30 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/18 11:13:30 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETE_HPP
#define DELETE_HPP

#include "lib.hpp"
#include "Post.hpp"

class Delete : public Post
{
	public:

		Delete( string message ) : Post(message) {}
		~Delete() {}
		void	deleteResource();
		void	printMother();
};


#endif
