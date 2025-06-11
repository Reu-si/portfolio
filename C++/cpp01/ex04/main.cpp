/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:17:16 by hreusing          #+#    #+#             */
/*   Updated: 2025/05/27 19:39:01 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replace.hpp"

int main(int argc, char **argv)
{
	if (argc == 4)
	{
		std::string filename = argv[1];
		std::string toReplace = argv[2];
		if (toReplace.empty())
		{
			std::cerr << "Error: s1 must not be empty.\n";
        	return 1;
		}
		std::string replacement = argv[3];
		std::ifstream inFile(filename);
		if (!inFile)
		{
			std::cerr << "Error: Could not open file " << filename << "\n" << std::endl;
			return 1;
		}
		std::ofstream outFile(filename + ".replace");
		if (!outFile)
		{
			std::cerr << "Error: Could not create output file" << filename << ".replace\n" << std::endl;
			return 1;
		}
		std::string line;
		while (std::getline(inFile, line))
		{
			outFile << ft_replace_all(line, toReplace, replacement) << std::endl;
		}
		inFile.close();
		outFile.close();
		return 0;
	}
	std::cerr << "Usage: " << argv[0] << " <filename> <string_to_replace> <replacement_string>" << std::endl;
	return 1;

}
