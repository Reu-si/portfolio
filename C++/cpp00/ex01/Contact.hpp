/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:03:35 by hreusing          #+#    #+#             */
/*   Updated: 2025/05/22 20:08:53 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP
#include <iostream>

class Contact
{
	private:
		std::string first_name;
		std::string last_name;
		std::string nickname;
		std::string phone_number;
		std::string darkest_secret;
	public:
		void setFirstName(std::string name) { this->first_name = name; }
		void setLastName(std::string name) { this->last_name = name; }
		void setNickname(std::string name) { this->nickname = name; }
		void setPhoneNumber(std::string number) { this->phone_number = number; }
		void setDarkestSecret(std::string secret) { this->darkest_secret = secret; }
		std::string getFirstName() { return first_name; }
		std::string getLastName() { return last_name; }
		std::string getNickname() { return nickname; }
		std::string getPhoneNumber() { return phone_number; }
		std::string getDarkestSecret() { return darkest_secret; }
};

#endif