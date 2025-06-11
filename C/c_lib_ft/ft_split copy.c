/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:46:23 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/11 13:39:25 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && (s[i - 1] == c || i == 0))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static	char	*ft_wordcpy(char const *s, int start, int end)
{
	char	*word;
	size_t	i;

	i = 0;
	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static	void	*ft_free_arr(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

static	char	**ft_split_arr(char **str, const char *s, char c)
{
	size_t	start;
	size_t	i;
	size_t	k;

	i = 0;
	start = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (s[i + 1] == c || s[i + 1] == '\0')
			{
				str[k] = ft_wordcpy(s, start, i + 1);
				if (str[k] == NULL)
					return (ft_free_arr(str));
				k++;
			}
		}
		i++;
		if (s[i - 1] == c)
			start = i;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	words;

	words = ft_word_count(s, c);
	str = (char **)malloc((words + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	str = ft_split_arr(str, s, c);
	str[words] = NULL;
	return (str);
}

// int	main(void)
// {
// 	//char	*str;
// 	char	**dest;
// 	int		i;
// 	char *s = "split  ||this|for|me|||||!|";
// 	char **result = ft_split(s, '|');

// 	i = 0;
// 	//str = " Hallo wie gehtss   ";
// 	//str = " Hallo";
// 	dest = ft_split("hello!zzzzzzzz", 'z');
// 	while (dest[i])
// 		printf("%s\n", result[i++]);
// }
