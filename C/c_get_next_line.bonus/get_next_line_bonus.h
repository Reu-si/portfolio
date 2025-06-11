/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:35:57 by hreusing          #+#    #+#             */
/*   Updated: 2024/06/04 16:22:27 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	int				fd;
	char			*str_buf;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);

char	*ft_get_line_as_str(t_list *list, char *str);

void	ft_create_list(t_list **list, int fd);
void	ft_dealloc(t_list **list, char *buf, int fd);
void	ft_lst_to_str(t_list *src_lst, char *dest);
void	ft_get_unused_chars(t_list **list, int fd);
void	ft_copy_str(t_list *src_ls, char *dest);
void	ft_lstappend(t_list **lst, char *buf, int fd);
t_list	*ft_lstlast(t_list *lst);

int		ft_found_newline(t_list *list);
size_t	ft_lenof_line(t_list *list);

#endif