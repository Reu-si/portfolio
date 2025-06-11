NAME = libftprintf.a
SRCS = \
	ft_printf.c ft_print_str.c ft_print_char.c ft_print_digit.c \
	ft_print_adress.c ft_strlen.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
#
#.PHONY: all clean fclean re