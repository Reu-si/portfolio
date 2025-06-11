/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:17:16 by hreusing          #+#    #+#             */
/*   Updated: 2025/05/27 16:56:54 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main() 
{
    std::string str;
	str = "HI THIS IS BRAIN";
	std::string* stringPTR;
	stringPTR = &str;
	std::string& stringREF = str;

	// Print memory addresses
    std::cout << "Memory address of brain:      " << &str << std::endl;
    std::cout << "Memory address held by stringPTR: " << stringPTR << std::endl;
    std::cout << "Memory address held by stringREF: " << &stringREF << std::endl;

    // Print values
    std::cout << "Value of brain:               " << str << std::endl;
    std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
    std::cout << "Value pointed to by stringREF: " << stringREF << std::endl;

    return 0;
}
