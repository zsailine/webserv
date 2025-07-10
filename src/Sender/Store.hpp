/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Store.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitandri <mitandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:11:53 by mitandri          #+#    #+#             */
/*   Updated: 2025/07/10 13:49:48 by mitandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STORE_HPP
#define STORE_HPP

#include "lib.hpp"
#include "class.hpp"

class Store
{
	private:

		std::string					_http;
		std::string					_path;
		std::string					_answer;
		static std::vector<string>	_storer;
		
	public:

		Store() {}
		~Store() {}
		void		storeData( string &message );
		void		printStorer() const; // can delete at the end
		void		sendAnswer( int &status, string &description, ServerResponse &ref );
		void		generateAlready();
		void		generateNew();
		void		setPath( std::string path );
		std::string	getHttp() const;
		std::string	getAnswer() const;
		std::string	getPath() const;
};

#endif
