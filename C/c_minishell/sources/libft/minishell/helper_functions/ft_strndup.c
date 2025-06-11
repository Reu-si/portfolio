/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:32:10 by pbohme            #+#    #+#             */
/*   Updated: 2024/11/15 17:43:32 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*des;
	size_t	len;
	size_t	i;

	len = 0;
	while (len < n && s[len])
		len++;
	des = (char *)malloc((len + 1) * sizeof(char));
	if (des == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		des[i] = s[i];
		i++;
	}
	des[len] = '\0';
	return (des);
}

/*int	main(void)
{
	char *str = "Hello world! i love u.";
	size_t	n = 4;
	int	i = 0;

	while (i < 3)
	{
		str++;
		i++;
	}
	printf("newstr: %s\n", ft_strndup(str, n));
	return (0);
}*/