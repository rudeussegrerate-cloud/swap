NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRCS = ft_printf.c ft_putstr.c ft_putchar.c ft_putnbr.c \
		ft_hexa_pointer.c ft_hexa_maj.c ft_hexa_min.c \
		ft_count_len.c ft_putunbr.c ft_putfloat.c

OBJ = $(SRCS:.c=.o)

HEADER = ft_printf.h 

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -c $(SRCS) -I .
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all  re clean fclean