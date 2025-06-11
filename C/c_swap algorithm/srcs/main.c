/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:26:31 by hreusing          #+#    #+#             */
/*   Updated: 2024/08/29 12:59:58 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_error(char *message, t_stack **stack_a)
{
	ft_free(stack_a);
	ft_printf("Error:  \n%s", message);
	exit(1);
}

int	ft_atoi2(char *str, t_stack **stack_a, char **arr)
{
	int				sign;
	long long int	result;
	int				i;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			ft_error("Non-numbers in string\n", stack_a);
		result = result * 10 + (str[i++] - '0');
	}
	if ((sign * result) > 2147483647 || (sign * result) < -2147483648)
		ft_free_str_stack(stack_a, arr);
	return (result * sign);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;

	stack_a = NULL;
	if (argc < 2)
		exit(1);
	if (argc > 1)
	{
		if (ft_check_args(argc, argv, &stack_a))
			ft_error("Error: arguments wrong\n", &stack_a);
		if (ft_check_dup(stack_a))
			ft_error("Duplicates present\n", &stack_a);
		if (!ft_check_sorted(stack_a))
			ft_sort(&stack_a);
		ft_free(&stack_a);
		return (0);
	}
}

/*
	while ((stack_a)->next)
		{
			printf("nbr: %lli\n", (stack_a)->nbr);
			stack_a = (stack_a)->next;
		}
		printf("nbr: %lli\n", (stack_a)->nbr);
*/