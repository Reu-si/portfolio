/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:17:16 by hreusing          #+#    #+#             */
/*   Updated: 2025/05/27 19:38:53 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replace.hpp"

std::string	ft_replace_all(std::string line, std::string s1, std::string s2)
{
	std::size_t	pos = 0;
	std::size_t	found;
	std::string	replacement;
	if (!s1.compare(s2))
		return (line);
	while ((found = line.find(s1, pos)) != std::string::npos)
	{
		replacement.append(line, pos, found - pos);
		replacement.append(s2);
		pos = found + s1.length();
	}
	replacement.append(line, pos);
	return (replacement);
}
