# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 12:27:25 by hreusing          #+#    #+#              #
#    Updated: 2024/08/29 12:28:22 by hreusing         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Werror -Wextra -I/home/hreusing/libft
#CFLAGS = -Wall -Werror -Wextra -I../../libft

SRCS = srcs/main.c srcs/stack_ops1.c srcs/stack_ops2.c srcs/apply.c \
		srcs/free.c srcs/cases.c srcs/checks.c srcs/find_index.c \
		srcs/sort.c srcs/swap_ops1.c srcs/swap_ops2.c srcs/swap_ops3.c \
		srcs/rotate_types.c srcs/cases_a.c
		
OBJS = $(SRCS:%.c=%.o)

LIBFT_DIR = /home/hreusing/libft
#LIBFT_DIR = ../../libft

all: $(NAME)

$(NAME): $(OBJS) libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft: 
	$(MAKE) -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

#.PHONY: all clean fclean re
