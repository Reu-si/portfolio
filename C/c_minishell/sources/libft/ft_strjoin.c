/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:01:07 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/03 19:35:11 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(char const *s1, char const *s2);

char	*ft_checkstr(char const *s1, char const *s2)
{
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	else
		return (ft_strdup(""));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	if ((!s1 && !s2) || (s1 && !s2) || (!s1 && s2))
		return (ft_checkstr(s1, s2));
	new = (char *)malloc(ft_len(s1, s2) * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_len(char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
		i++;
	j = 0;
	while (s2[j] != '\0')
	{
		i++;
		j++;
	}
	return (i + 1);
}

/*int	main(void)
{
	char	s1[] = "Hello";
	char	s2[] = "world";

	printf("%s\n", ft_strjoin(s1, s2));
	return (0);
}*/
