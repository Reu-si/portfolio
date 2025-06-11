/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:38:04 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 15:47:39 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L

# include <string.h>
# include <ctype.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <linux/limits.h>
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>
# include <termios.h>

# include "../sources/libft/ft_printf.h"
# include "../sources/libft/libft.h"
# include "AST.h"

# define INITIAL_TOKEN_SIZE 32
# define MAX_EXIT_CODE 255

// global variable to indicate received signal
extern volatile sig_atomic_t	g_signum;

typedef struct s_token 
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_mini
{
	int				cmd_count;
	int				word_count;
	char			**our_env;
	int				exit_code;
	int				is_last_cmd;
	int				current_cmd;
	int				has_redirection;
	int				org_stdin;
	int				org_stdout;
	int				fork;
	int				is_terminal;
	struct termios	old_term;
}	t_mini;

typedef struct s_strtol
{
	const char		*s;
	unsigned long	acc;
	int				neg;
	unsigned long	cutoff;
}	t_stol;

typedef struct s_exp_quote
{
	int		var_len;
	char	*exit_code_str;
	char	*expanded_str;
	char	*expanded_value;
	char	*var_name;
	char	*str;
	size_t	new_len;
}	t_exp_quote;

//main and init
t_mini	*ft_init_mini(char **envp);
void	handle_input_signals(t_mini *mini);
int		handle_null_input(t_AN **ast, t_token **tokens, char **input);
int		handle_empty_or_invalid_input(char **input, t_mini *mini);
int		process_input(char **input, t_token **tokens, t_mini *mini);
int		process_ast(t_AN **ast, t_token **tokens, t_mini *mini, char **input);
void	ft_handle_signals_non_interactive(void);
void	ft_handle_signals_interactive(void);
void	ft_reset_line(int sig);
void	ft_display_new_line(int sig);
void	ft_signal_exitcode(t_mini *mini);
void	ft_save_term_attr(t_mini *mini);
void	ft_reset_term_attr(t_mini *mini);
char	*ft_read_cmd(void);
t_stol	*set_stl_struct(const char *nptr, int *base);

//helper
int		is_whitespace(char c);
void	skip_whitespace(const char **input);
int		only_whitespace(char *str);
char	*ft_sprintf_simple(const char *key, const char *value);
char	**create_env_copy(char **envp);
long	ft_stol(const char *nptr, char **endptr, int base);
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isupper(int c);
void	ft_printf_stderr(char *s1, char *s2, char *s3);
char	*ft_strcpy(char *dst, const char *src);
void	ft_snprintf(char *full_path, char *dir, char *command);
char	*ft_getenv(const char *name, t_mini *mini);

//tokenize
t_token	*create_token(const char *value, t_token_type type);
t_token	*tokenize_input(const char *input);
void	append_to_list(t_token **head, t_token **tail, t_token *new);
int		ft_tokenize_pipe(t_token **head, t_token **tail);
int		ft_tokenize_quotes(t_token **head, t_token **tail, const char **input);
int		ft_tokenize_red_app_her(t_token **head, t_token **tail, \
		const char **input);
int		ft_tokenize_com_arg(t_token **head, t_token **tail, const char **input);
char	*get_env_value(const char *var_name, char **envp);
int		check_expansion(t_token **tokens, char **envp, t_mini *mini);
void	check_quote_expansion(t_token *token, char *str, \
			char **envp, int exit_code);
int		check_reg_expansion(t_token **tokens, t_mini **mini);
void	rewrite_tokens(t_token **head, t_token *current, \
			char *expanded_value);
int		valid_cmd(t_token *tokens, t_mini *mini);
char	*clean_input(const char **input, char quote);
int		check_quote_position(char *input, int double_quote, int single_quote);
int		check_quote_count(char *input);
int		type_is_cmd_arg(t_token_type type);
int		type_is_red_app_her(t_token_type type);
void	calculate_new_str(char *str, t_exp_quote **new, char **envp);
void	fill_expanded_str(t_exp_quote **new, char **envp);

//AST
t_AN	*build_ast(t_token *tokens, t_mini *mini, \
				t_AN *root);
t_AN	*create_pipeline_node(void);
t_AN	*create_cmd_node(char *name);
t_AN	*create_red_node(t_token_type type, char *file, t_mini *mini);
void	add_to_pipeline(t_AN *pipeline, t_AN *node);
void	add_arg_to_command(t_AN *command, char *arg);
void	add_red_to_cmd(t_AN *cmd, t_AN *red);
void	cmd_node(t_AN **current_cmd, t_AN *root, char *value);

//builtin
int		is_builtin(char *cmd);
void	execute_builtin(char *cmd, char **args, char ***envp, t_mini *mini);
void	ft_pwd(void);
void	ft_env(char **envp);
void	ft_echo(char **args, t_mini *mini);
void	ft_cd(char **args, t_mini *mini);
void	ft_export(char **args, char ***envp, t_mini *mini);
void	ft_unset(char **args, t_mini *mini);
bool	ft_exit(char **args, t_mini *mini);
int		is_valid_identifier(const char *key);
int		ft_setenv(const char *key, size_t key_len, \
			const char *value, t_mini *mini);
char	*ft_strtok(char *str, const char *delim);
int		ft_unsetenv(char *key, size_t key_len, t_mini *mini);
void	check_for_eq_sign(char *args, char **key, char **value);

//execute
char	*ft_find_path(char *cmd, t_mini *mini);
char	*find_executable_in_paths(char **all_paths, char *cmd);
void	execute_ast(t_AN *ast, t_mini *mini);
int		setup_pipeline(int i, t_mini *mini, t_AN *ast, int *pipe_fd);
void	create_pipes(int *prev_pipe_read, int *pipe_fd, t_mini *mini);
void	setup_pipes(int input_fd, int output_fd, int is_last_cmd);
void	cleanup_pipes(int *prev_pipe_read, int *pipe_fd, t_mini *mini);
void	handle_pid_error(pid_t *pids, char *error);
int		handle_single_builtin(t_AN *ast, t_mini *mini);
int		exec_cmd(t_AN *node, t_mini *mini);
void	execute_command_with_args(t_AN *node, char *path, t_mini *mini);
void	execute_with_path_lookup(t_AN *node, t_mini *mini);
void	execute_absolute_path(t_AN *node, t_mini *mini);
void	fork_and_execute_command(t_AN *node, int prev_pipe_read, \
			int pipe_fd[2], t_mini *mini);
void	execute_pipeline(t_AN *ast, t_mini *mini);
void	handle_parent_process(t_AN *ast, pid_t *pids, t_mini *mini);
int		ft_create_file(t_AN *node, t_mini *mini);
int		ft_setup_redirection(t_AN *node, t_mini *mini, char *cmd);
int		ft_handle_fds(char *file, int open_type, t_mini *mini, char *cmd);
int		ft_open_file(char *file, int open_type, int *err);
void	handle_file_error(int err, char *file, t_mini *mini);
void	ft_reset_fd(int	*heredoc_fd, const char *heredoc_file, t_mini *mini);
void	ft_handle_heredoc(char *delimiter, t_mini *mini);
void	signal_heredoc_handler(int sig);
void	ft_setup_heredoc_signals(t_mini *mini);
void	ft_write_heredoc_content(int fd, char *delimiter);
int		ft_fork_heredoc(char *delimiter, t_mini *mini);
int		ft_open_heredoc_file(t_mini *mini);
void	ft_handle_heredoc_child(t_mini *mini, int heredoc_fd, char *delimiter);
void	ft_wait_for_heredoc(pid_t pid, t_mini *mini);
void	ft_init_pipes(int *prev_pipe_read, int *pipe_fd);

//free
void	free_tokens(t_token *head);
void	free_ast(t_AN *node);
void	free_redirection_nodes(t_AN *node);
void	free_command_node(t_AN *node);
void	free_mini(t_mini *mini);
void	ft_free_all(t_AN **ast, t_mini **mini, char **input, \
			t_token **tokens);

#endif 
