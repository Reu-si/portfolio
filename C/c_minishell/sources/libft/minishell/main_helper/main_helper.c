/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:40:57 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 13:23:05 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_input_signals(t_mini *mini)
{
	ft_handle_signals_interactive();
	if (g_signum)
		ft_signal_exitcode(mini);
}

int	handle_null_input(t_AN **ast, t_token **tokens, char **input)
{
	if (*input == NULL)
	{
		ft_free_all(ast, NULL, input, tokens);
		printf("exit\n");
		return (1);
	}
	return (0);
}

int	handle_empty_or_invalid_input(char **input, t_mini *mini)
{
	if (only_whitespace(*input) || (*input)[0] == '\0' || (*input)[0] == '\n')
	{
		free(*input);
		return (1);
	}
	if (((*input)[0] == '\'' && (*input)[1] == '\'' && \
		((*input)[2] == ' ' || (*input)[2] == '\0')) || \
		((*input)[0] == '\"' && (*input)[1] == '\"' && ((*input)[2] == ' ' \
		|| (*input)[2] == '\0')))
	{
		ft_putendl_fd("minishell$: : command not found", 2);
		free(*input);
		mini->exit_code = 127;
		return (1);
	}
	return (0);
}

int	process_input(char **input, t_token **tokens, t_mini *mini)
{
	*tokens = tokenize_input(*input);
	if (!*tokens)
	{
		free(*input);
		return (1);
	}
	if (check_expansion(tokens, mini->our_env, mini) == 1)
	{
		free(*input);
		return (1);
	}
	if (valid_cmd(*tokens, mini) != 0)
	{
		ft_free_all(NULL, NULL, input, tokens);
		return (1);
	}
	return (0);
}

int	process_ast(t_AN **ast, t_token **tokens, t_mini *mini, char **input)
{
	*ast = build_ast(*tokens, mini, *ast);
	if (!*ast)
	{
		ft_free_all(NULL, NULL, input, tokens);
		return (1);
	}
	execute_ast(*ast, mini);
	ft_free_all(ast, NULL, input, tokens);
	return (0);
}
