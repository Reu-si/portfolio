/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:35:36 by hreusing          #+#    #+#             */
/*   Updated: 2024/06/04 17:28:32 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_get_unused_chars(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	char	*buf;
	int		i;
	int		j;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	clean_node = malloc(sizeof(t_list));
	if (buf == NULL || clean_node == NULL)
		return ;
	last_node = ft_lstlast(*list);
	i = 0;
	j = 0;
	while (last_node -> str_buf[i] != '\n' && last_node -> str_buf[i] != '\0')
		i++;
	while (last_node -> str_buf[i++] != '\0')
		buf[j++] = last_node -> str_buf[i];
	buf[j] = '\0';
	clean_node -> str_buf = buf;
	clean_node -> next = NULL;
	ft_dealloc(list, clean_node, buf);
}

char	*ft_get_line_as_str(t_list *list)
{
	size_t	str_len;
	char	*str;

	str_len = ft_lenof_line(list);
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str == NULL)
		return (NULL);
	ft_lst_to_str(list, str);
	return (str);
}

int	ft_found_newline(t_list *list)
{
	size_t	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list -> str_buf[i])
		{
			if (list -> str_buf[i] == '\n')
			{
				return (1);
			}
			i++;
		}
		list = list -> next;
	}
	return (0);
}

void	ft_create_list(t_list **list, int fd)
{
	int		chars_read;
	char	*buf;

	while (!ft_found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (!chars_read || chars_read == -1)
		{
			free(buf);
			return ;
		}
		buf[chars_read] = '\0';
		ft_lstappend(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = ft_get_line_as_str(list);
	ft_get_unused_chars(&list);
	return (next_line);
}

// int main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		lines_read;

// 	fd = open("test.txt", O_RDONLY);
// 	lines_read = 1;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%d-> %s\n", lines_read++, line);
// 		free(line);
// 		line = NULL;
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	return (0);
// }
