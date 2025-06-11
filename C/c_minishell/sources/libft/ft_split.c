/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:11:00 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/07 10:41:46 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_rows(char const *s, char c)
{
	int	rows;
	int	i;

	rows = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			rows++;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	return (rows);
}

int	ft_worlen(char const *s, char c)
{
	int	m;

	m = 0;
	while (s[m] && s[m] != c)
		m++;
	return (m);
}

void	ft_free(int k, char **array)
{
	while (k > 0)
	{
		k--;
		free(array[k]);
	}
	free(array);
}

char	**ft_part_split(char **array, char const *s, char c, int words)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (k < words)
	{
		while (s[i] && s[i] == c)
			i++;
		array[k] = ft_substr(s, i, ft_worlen(&s[i], c));
		if (!(array[k]))
		{
			ft_free(k, array);
			return (NULL);
		}
		while (s[i] && s[i] != c)
			i++;
		k++;
	}
	array[k] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		words;

	if (!s)
		return (NULL);
	words = ft_rows(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	ft_part_split(array, s, c, words);
	return (array);
}

/*int	main(void)
{
	char const	s[] = "--2--3--5---34";
	char		c;
	char		**arr;
	int		i;

	c = '-';
	arr = ft_split(s, c);
	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	return (0);
}*/
