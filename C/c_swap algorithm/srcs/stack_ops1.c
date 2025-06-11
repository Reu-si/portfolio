/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:26:45 by hreusing          #+#    #+#             */
/*   Updated: 2024/08/29 12:26:46 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_stackadd_back(t_stack **lst, t_stack *new)
{
	if (!lst)
		return ;
	if (!(*lst))
		*lst = new;
	else
		(ft_stack_last(*lst))->next = new;
}

t_stack	*ft_stacknew(int content, t_stack **stack_a)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new)
		ft_error("Error: memory allocation did not work", stack_a);
	new -> nbr = content;
	new -> next = NULL;
	return (new);
}

int	ft_stack_size(t_stack *lst)
{
	size_t	i;
	t_stack	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp -> next;
		i++;
	}
	return (i);
}

void	ft_stack_add_front(t_stack **stack, t_stack *new)
{
	t_stack	*tmp;

	if (*stack == NULL)
	{
		*stack = new;
		return ;
	}
	tmp = *stack;
	*stack = new;
	new -> next = tmp;
}

t_stack	*ft_stack_last(t_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
