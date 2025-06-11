#include <iostream>

char	toupper(char c)
{
	if(c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

int	main(int argc, char **argv )
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			for (int j = 0; argv[i][j]; j++)
				std::cout << toupper(argv[i][j]);
			if (i != argc - 1)
				std::cout << " ";
		}
		std::cout << "\n";
	}
	else
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
	return (0);
}

// was soll bei "" gemacht werden? oder "   "