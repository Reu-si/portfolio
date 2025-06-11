/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:47:37 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/01 15:22:34 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_isnull(void)
{
	char	*num;

	num = (char *)malloc(2 * sizeof(char));
	if (!num)
		return (NULL);
	num[0] = '0';
	num[1] = '\0';
	return (num);
}

char	*ft_maxn(void)
{
	char	*num;

	num = (char *)malloc(12 * sizeof(char));
	if (!num)
		return (NULL);
	num[0] = '-';
	num[1] = '2';
	num[2] = '1';
	num[3] = '4';
	num[4] = '7';
	num[5] = '4';
	num[6] = '8';
	num[7] = '3';
	num[8] = '6';
	num[9] = '4';
	num[10] = '8';
	num[11] = '\0';
	return (num);
}

void	ft_fillstr(int n, char *num, int dig)
{
	int	tem;

	num[dig] = '\0';
	tem = n;
	if (tem < 0)
		tem = -tem;
	dig--;
	while (dig >= 0)
	{
		num[dig] = (tem % 10) + '0';
		tem /= 10;
		dig--;
	}
	if (n < 0)
		num[0] = '-';
}

char	*ft_itoa(int n)
{
	int		dig;
	int		tem;
	char	*num;

	if (n == 0)
		return (ft_isnull());
	if (n == -2147483648)
		return (ft_maxn());
	tem = n;
	dig = 0;
	while (tem != 0)
	{
		tem /= 10;
		dig++;
	}
	if (n < 0)
		dig++;
	num = (char *)malloc((dig + 1) * sizeof(char));
	if (!num)
		return (NULL);
	ft_fillstr(n, num, dig);
	return (num);
}

/*int	main(void)
{
	int	i;

	i = -2147483648;
	printf("%s\n", ft_itoa(i));
	return (0);
}*/
