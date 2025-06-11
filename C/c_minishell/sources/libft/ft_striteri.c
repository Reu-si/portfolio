/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:48:44 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/01 15:26:45 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*void	ft_toupper(unsigned int i, char *s)
{
	if ((i % 2 == 0) && (*s >= 'a' || *s <= 'z'))
		*s = *s - 32;
}

int	main(void)
{
	char	s[] = "helloworld";

	printf("%s\n", s);
	ft_striteri(s, ft_toupper);
	printf("%s\n", s);
	return (0);
}*/
