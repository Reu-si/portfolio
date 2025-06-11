/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:46:50 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/05 16:25:18 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = 0;
	while (s[i])
	{
		if (s[i] == (char )c)
			str = (char *)(s + i);
		i++;
	}
	if (s[i] == (char )c)
		str = (char *)(s + i);
	return (str);
}

/*int	main(void)
{
	const char str[] = "helloagain";
	int c = 97;

	printf("%s\n", ft_strrchr(str, c));
	return (0);
}*/
