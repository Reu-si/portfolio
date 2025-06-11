/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:49:09 by hreusing          #+#    #+#             */
/*   Updated: 2025/05/27 16:23:41 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <iostream>

class Zombie
{
	private:
		std::string name;
	public:
		void announce(void);
		Zombie(std::string name) : name(name) {}
   		~Zombie() {
        std::cout << name << " has been destroyed.\n";
    }
};

void randomChump(std::string name);
Zombie* newZombie(std::string name);

#endif