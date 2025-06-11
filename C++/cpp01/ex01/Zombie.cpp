/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:49:57 by hreusing          #+#    #+#             */
/*   Updated: 2025/05/27 16:48:52 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"


// Default constructor (required by new Zombie[N])
Zombie::Zombie() {}

// Constructor with name
Zombie::Zombie(std::string name) : name(name) {}

// Destructor
Zombie::~Zombie() {
    std::cout << name << " has been destroyed.\n";
}
void Zombie::setName(std::string name) {
    this->name = name;
}

void Zombie::announce(void) {
    std::cout << name << ": BraiiiiiiinnnzzzZ...\n";
}