/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:45:22 by pbohme            #+#    #+#             */
/*   Updated: 2024/12/02 15:36:07 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char )s1[i] - (unsigned char )s2[i]);
}

// int	main(void)
// {
// 	char *s1 = "helloA";
// 	char *s2 = "A";

// 	printf("result: %d\n", ft_strcmp(s1, s2));
// 	return (0);
// }