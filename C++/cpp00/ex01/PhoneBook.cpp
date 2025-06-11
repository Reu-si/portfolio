/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:54:56 by hreusing          #+#    #+#             */
/*   Updated: 2025/05/22 17:30:47 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iomanip>

void printColumn(std::string str) {
    if (str.length() > 10)
        std::cout << std::setw(10) << str.substr(0, 9) + ".";
    else
        std::cout << std::setw(10) << str;
}

void PhoneBook::add()
{
	Contact contact;
	std::string input;

	if (this->index >= 8)
		this->index = 0;
	std::cout << "Enter first name: ";
	do {
        std::getline(std::cin, input);
        if (input.empty())
            std::cout << "Input cannot be empty. Enter first name: ";
    } while (input.empty());
	contact.setFirstName(input);
	std::cout << "Enter last name: ";
	do {
        std::getline(std::cin, input);
        if (input.empty())
            std::cout << "Input cannot be empty. Enter last name: ";
    } while (input.empty());
	contact.setLastName(input);
	std::cout << "Enter nickname: ";
	do {
        std::getline(std::cin, input);
        if (input.empty())
            std::cout << "Input cannot be empty. Enter nickname: ";
    } while (input.empty());
	contact.setNickname(input);
	std::cout << "Enter phone number: ";
	do {
        std::getline(std::cin, input);
        if (input.empty())
            std::cout << "Input cannot be empty. Enter phone number: ";
    } while (input.empty());
	contact.setPhoneNumber(input);
	std::cout << "Enter darkest secret: ";
	do {
        std::getline(std::cin, input);
        if (input.empty())
            std::cout << "Input cannot be empty. Enter darkest secret: ";
    } while (input.empty());
	contact.setDarkestSecret(input);
	std::cout << "Contact added.\n";
	phonebook[this->index] = contact;
	this->index++;
	if (this->count < 8)
        this->count++;
}

void PhoneBook::search()
{
	std::cout << std::setw(10) << "Index" << "|"
	<< std::setw(10) << "First Name" << "|"
	<< std::setw(10) << "Last Name" << "|"
	<< std::setw(10) << "Nickname" << std::endl;
	for (int i = 0; i < this->count; i++) {
        std::cout << std::setw(10) << i << "|";
        printColumn(phonebook[i].getFirstName());
        std::cout << "|";
        printColumn(phonebook[i].getLastName());
        std::cout << "|";
        printColumn(phonebook[i].getNickname());
        std::cout << std::endl;
    }
	std::cout << "Enter the index of the contact to display: ";
    std::string input;
    std::getline(std::cin, input);
	if (input.length() == 1 && isdigit(input[0])) {
        int i = input[0] - '0';
        if (i >= 0 && i < index) {
            Contact c = phonebook[i];
            std::cout << "First Name: " << c.getFirstName() << std::endl;
            std::cout << "Last Name: " << c.getLastName() << std::endl;
            std::cout << "Nickname: " << c.getNickname() << std::endl;
            std::cout << "Phone Number: " << c.getPhoneNumber() << std::endl;
            std::cout << "Darkest Secret: " << c.getDarkestSecret() << std::endl;
        } else {
            std::cout << "Invalid index.\n";
        }
    } else {
        std::cout << "Invalid input.\n";
    }
}

int main() 
{
	PhoneBook phonebook;
	std::string input;

	phonebook.init();
	while(true)
	{
		std::getline(std::cin, input);
		if (input == "ADD")
			phonebook.add();
		else if (input == "SEARCH")
			phonebook.search();
		else if (input == "EXIT")
			break;  // muss noch etwas free??
	}
	return 0;
}