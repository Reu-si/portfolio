/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:02:04 by hreusing          #+#    #+#             */
/*   Updated: 2025/05/27 17:47:15 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon() {};

Weapon::Weapon(std::string type) : type(type) {}

const std::string& Weapon::getType() const {
	return type;
}

void Weapon::setType(std::string type) {
	this->type = type;
}