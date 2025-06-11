/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:09:48 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/05 17:22:58 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_empty_s(void)
{
	char	*sub;

	sub = (char *)malloc(1 * sizeof(char));
	if (!sub)
		return (NULL);
	sub[0] = '\0';
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			i;
	unsigned int	j;

	if (!s)
		return (NULL);
	i = 0;
	j = start;
	if (ft_strlen(s) < start)
		return (ft_empty_s());
	while (s[j++] != '\0' && i < len)
		i++;
	sub = (char *)malloc((i + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	i = 0;
	j = start;
	while (s[j] != '\0' && i < len)
		sub[i++] = s[j++];
	sub[i] = '\0';
	return (sub);
}

/*int	main(void)
{
	//const char	s[] = "Helloworld!";
	//unsigned int	start = 5;
	//size_t		len = 12;
	char		*r;

	r = ft_substr("hola", 4294967295, 0);
	printf("%s\n", r);
	printf("%i\n", ft_strncmp(r, "", 3));
	free(r);
	return (0);
}*/
