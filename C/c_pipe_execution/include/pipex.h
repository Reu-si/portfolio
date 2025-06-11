/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:47:28 by hreusing          #+#    #+#             */
/*   Updated: 2024/07/22 13:47:49 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_pipex
{
	int		fdin;
	int		fdout;
	int		here_doc;
	int		is_invalid_infile;
	char	**cmd_paths;
	char	***cmd_args;
	int		cmd_count;
}	t_pipex;

void	ft_init_pipex(t_pipex *pipe, char **argv, char **envp);
int		ft_count_args(char **argv);
char	***ft_parse_args(char **argv, int arg_count);
char	**ft_find_paths(char ***cmds, char **envp, int arg_count);
char	*ft_get_right_path(char **all_paths, char *cmd);
void	ft_free_path(char **paths);
void	error(char *message, char *type);
void	ft_free_cmds(t_pipex *pip);
void	ft_free_pipe(t_pipex *pip);

#endif