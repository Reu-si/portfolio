/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:17:16 by hreusing          #+#    #+#             */
/*   Updated: 2025/05/27 16:51:34 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() 
{
    randomChump("Stacky");
    
    Zombie* z = newZombie("Heapy");
    z->announce();
    delete z;

    return 0;
}
