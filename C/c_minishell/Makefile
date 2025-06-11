NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -lreadline

SRCS = sources/minishell/main.c \
	sources/minishell/main_helper/main_helper.c \
	sources/minishell/main_helper/helper.c \
	sources/minishell/main_helper/free.c \
	sources/minishell/main_helper/free_helper.c \
	sources/minishell/main_helper/validate_command.c \
	sources/minishell/tokenizing/tokenize.c \
	sources/minishell/tokenizing/tokenize_helper.c \
	sources/minishell/tokenizing/tokenize_quotes.c \
	sources/minishell/tokenizing/tokenize_com_arg.c \
	sources/minishell/tokenizing/tokenize_r_a_h_p.c \
	sources/minishell/tokenizing/cleaned_input.c \
	sources/minishell/tokenizing/expansion.c \
	sources/minishell/tokenizing/expansion_reg.c \
	sources/minishell/tokenizing/expansion_quote.c \
	sources/minishell/tokenizing/expansion_quote_helper.c \
	sources/minishell/tokenizing/rewrite_tokens.c \
	sources/minishell/builtin/builtin.c \
	sources/minishell/builtin/echo.c \
	sources/minishell/builtin/export.c \
	sources/minishell/builtin/exit.c \
	sources/minishell/builtin/env.c \
	sources/minishell/builtin/cd.c \
	sources/minishell/builtin/pwd.c \
	sources/minishell/builtin/unset.c \
	sources/minishell/builtin/export_helper.c \
	sources/minishell/AST/buildAST.c \
	sources/minishell/AST/buildAST_helper.c \
	sources/minishell/AST/ASTcreate_helper.c \
	sources/minishell/AST/addAST_helper.c \
	sources/minishell/execution/find_path.c \
	sources/minishell/execution/executeAST.c \
	sources/minishell/execution/pipes_helper.c \
	sources/minishell/execution/exec_cmd.c \
	sources/minishell/execution/redirections.c \
	sources/minishell/execution/heredoc.c \
	sources/minishell/execution/heredoc_fork.c \
	sources/minishell/execution/init_pipes.c \
	sources/minishell/signal/signal_handler.c \
	sources/minishell/signal/terminal_attributes.c \
	sources/minishell/helper_functions/ft_strcmp.c \
	sources/minishell/helper_functions/ft_strndup.c \
	sources/minishell/helper_functions/ft_strtol.c \
	sources/minishell/helper_functions/ft_strtol_helper.c \
	sources/minishell/helper_functions/ft_isupper.c \
	sources/minishell/helper_functions/ft_printf_stderr.c \
	sources/minishell/helper_functions/ft_sprintf_simple.c \
	sources/minishell/helper_functions/ft_strtok.c \
	sources/minishell/helper_functions/ft_snprintf.c \
	sources/minishell/helper_functions/ft_getenv.c \

OBJS = $(SRCS:.c=.o)

LIBFTDIR = sources/libft

LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) | $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LIBS)

$(LIBFT):
	make -C $(LIBFTDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re libft 
