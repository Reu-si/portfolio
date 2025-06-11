/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:19:00 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/05 17:43:18 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(char const *set, char const c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (ft_check(set, s1[start]) == 1)
		start++;
	if (start == ft_strlen(s1))
	{
		trim = ft_strdup("");
		if (trim == NULL)
			return (NULL);
		else
			return (trim);
	}
	while (ft_check(set, s1[end - 1]) == 1)
		end--;
	trim = ft_substr(s1, start, end - start);
	return (trim);
}

/*int	main(void)
{
	char	s1[] = "qqq abcd qq q";
	char	set[] = "q ";
	char	*goal;

	goal = ft_strtrim(s1, set);
	printf("%s\n", s1);
	printf("%s\n", goal);
	free(goal);
	return (0);
}*/
