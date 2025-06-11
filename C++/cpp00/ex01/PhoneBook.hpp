/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:55:06 by hreusing          #+#    #+#             */
/*   Updated: 2025/05/22 20:09:17 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP
#include <iostream>
#include "Contact.hpp"

class PhoneBook 
{
	private:
		Contact phonebook[8];
		int index;
		int	count;
	public:
		void init()
		{
			index = 0;
			count = 0;
			std::cout << "Please enter one of the three commands: ADD, SEARCH and EXIT\n";
		}
		void add();
		void search();
		void exit();
};
#endif