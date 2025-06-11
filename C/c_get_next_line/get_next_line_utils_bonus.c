/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:36:24 by hreusing          #+#    #+#             */
/*   Updated: 2024/06/04 16:46:35 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_lst_to_str(t_list *src_lst, char *dest)
{
	size_t	i;
	size_t	j;

	if (src_lst == NULL)
		return ;
	j = 0;
	while (src_lst)
	{
		i = 0;
		while (src_lst -> str_buf[i])
		{
			if (src_lst -> str_buf[i] == '\n')
			{
				dest[j++] = '\n';
				dest[j] = '\0';
				return ;
			}
			dest[j++] = src_lst -> str_buf[i++];
		}
		src_lst = src_lst -> next;
	}
	dest[j] = '\0';
}

size_t	ft_lenof_line(t_list *list)
{
	size_t	i;
	size_t	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list -> str_buf[i])
		{
			if (list -> str_buf[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list -> next;
	}
	return (len);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_lstappend(t_list **list, char *buf, int fd)
{
	t_list	*new;
	t_list	*last;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	last = ft_lstlast(list[fd]);
	if (last == NULL)
		list[fd] = new;
	else
		last -> next = new;
	new -> str_buf = buf;
	new -> next = NULL;
	return ;
}

void	ft_dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*temp;

	if (list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)-> next;
		free((*list)-> str_buf);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (clean_node -> str_buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
