/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:55:28 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/10 16:09:17 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*des;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	i++;
	des = (char *)malloc((i) * sizeof(char));
	if (des == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		des[i] = s[i];
		i++;
	}
	des[i] = '\0';
	return (des);
}

/*int	main(void)
{
	char	src[] = "helloagain!";
	char	*dupli;

	dupli = ft_strdup(src);
	printf("%s", dupli);
	free(dupli);
	return (0);
}*/
