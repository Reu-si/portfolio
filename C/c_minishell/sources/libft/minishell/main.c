/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:40:57 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 13:07:49 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_mini(t_mini **mini, char **envp)
{
	*mini = ft_init_mini(envp);
	if (!*mini)
	{
		ft_putendl_fd("Failed to initialize shell", 2);
		exit(1);
	}
}

void	ft_init_structs(int argc, t_mini **mini, t_token **tokens, t_AN **ast)
{
	if (argc != 1)
	{
		errno = EINVAL;
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	*mini = NULL;
	*tokens = NULL;
	*ast = NULL;
}

void	ft_process_all(char **input, t_token **tokens, \
			t_mini *mini, t_AN **ast)
{
	if (process_input(input, tokens, mini))
		return ;
	if (process_ast(ast, tokens, mini, input))
		return ;
}

void	ft_exit_process(int *ex, t_mini *mini)
{
	*ex = mini->exit_code;
	free_mini(mini);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_mini	*mini;
	t_AN	*ast;
	int		ex;

	(void)argv;
	ft_init_structs(argc, &mini, &tokens, &ast);
	init_mini(&mini, envp);
	while (1)
	{
		ft_save_term_attr(mini);
		handle_input_signals(mini);
		input = ft_read_cmd();
		if (handle_null_input(&ast, &tokens, &input))
			break ;
		if (handle_empty_or_invalid_input(&input, mini))
			continue ;
		ft_handle_signals_non_interactive();
		if (g_signum)
			ft_signal_exitcode(mini);
		ft_process_all(&input, &tokens, mini, &ast);
	}
	ft_exit_process(&ex, mini);
	return (ex);
}
