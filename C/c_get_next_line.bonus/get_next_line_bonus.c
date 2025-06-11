/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:35:36 by hreusing          #+#    #+#             */
/*   Updated: 2024/06/04 16:22:34 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_get_unused_chars(t_list **list, int fd)
{
	t_list	*last_node;
	char	*buf;
	int		i;
	int		j;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return ;
	last_node = ft_lstlast(*list);
	i = 0;
	j = 0;
	while (last_node -> str_buf[i] != '\n' && last_node -> str_buf[i] != '\0')
		i++;
	while (last_node -> str_buf[i++] != '\0')
		buf[j++] = last_node -> str_buf[i];
	buf[j] = '\0';
	ft_dealloc(list, buf, fd);
}

char	*ft_get_line_as_str(t_list *list, char *str)
{
	size_t	str_len;

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
		ft_lstappend(list, buf, fd);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_create_list(&list, fd);
	if (list[fd] == NULL)
		return (NULL);
	next_line = NULL;
	next_line = ft_get_line_as_str(list[fd], next_line);
	ft_get_unused_chars(&list[fd], fd);
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
