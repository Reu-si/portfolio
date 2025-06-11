# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 11:11:47 by marvin            #+#    #+#              #
#    Updated: 2025/01/22 11:11:47 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = zombie

CC = c++
CFLAGS = -Wall -Werror -Wextra

SRCS = main.cpp \
		newZombie.cpp \
		randomChump.cpp \
		Zombie.cpp
		
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


# gcc -fsanitize=thread -g -Wall -Wextra -Werror -o philo *.c -lpthread