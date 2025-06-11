/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:17:16 by hreusing          #+#    #+#             */
/*   Updated: 2025/05/27 16:51:26 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() 
{
    int N = 5;
    Zombie* horde = zombieHorde(N, "Bertram");

    if (!horde) {
        std::cerr << "Failed to create horde.\n";
        return 1;
    }

    for (int i = 0; i < N; i++) {
        horde[i].announce();
    }

    delete[] horde; // Free memory (important!)

    return 0;
}
