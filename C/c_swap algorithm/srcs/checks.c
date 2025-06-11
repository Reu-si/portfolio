/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:26:21 by hreusing          #+#    #+#             */
/*   Updated: 2024/08/29 13:19:03 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	ft_isnum(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '-' || num[0] == '+')
		i++;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_dup(t_stack *stack_a)
{
	t_stack	*current;
	t_stack	*compare;

	if (!stack_a)
		return (0);
	current = stack_a;
	while (current != NULL)
	{
		compare = current->next;
		while (compare != NULL)
		{
			if (current->nbr == compare->nbr)
				return (1);
			compare = compare->next;
		}
		current = current->next;
	}
	return (0);
}

int	ft_check_sorted(t_stack *stack_a)
{
	t_stack	*tmp;

	if (!stack_a || !stack_a->next)
		return (1); 
	tmp = stack_a;
	while (tmp->next)
	{
		if (tmp->nbr > tmp->next->nbr)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_check_string_args(char **argv, t_stack **stack_a)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	tmp = ft_split(argv[1], ' ');
	if (!tmp[1] || !tmp)
	{
		ft_free_arr(tmp);
		exit(1);
	}
	while (tmp[i])
	{
		j = ft_atoi2(tmp[i], stack_a, tmp);
		ft_stackadd_back(stack_a, ft_stacknew(j, stack_a));
		i++;
	}
	ft_free_arr(tmp);
}

int	ft_check_args(int argc, char **argv, t_stack **stack_a)
{
	int				i;
	long long int	j;

	if (argc == 2)
		ft_check_string_args(argv, stack_a);
	else
	{
		i = 1;
		while (i < argc)
		{
			j = ft_atoi2(argv[i], stack_a, NULL);
			ft_stackadd_back(stack_a, ft_stacknew(j, stack_a));
			i++;
		}
	}
	return (0);
}
