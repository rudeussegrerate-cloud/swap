NAME = push_swap
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = main.c error_free.c push_command.c simple_sort.c \
		push_swap_init.c reverse_rotate_command.c rotate_command.c \
		stack_init.c stack_utils.c swap_command.c tiny_sort.c disorder.c \
		medium_sort.c complex_sort.c bench.c operation.c
OBJS = $(SRCS:.c=.o)

HEADERS = push_swap.h

LIBFTPRINTF = ft_printf/libftprintf.a
LIBFT = libft/libft.a

all : $(NAME)

$(LIBFTPRINTF):
	make -C ft_printf
$(LIBFT):
	make -C libft

$(NAME) : $(OBJS) $(LIBFTPRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L./ft_printf -lftprintf -L./libft -lft -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	make -C ft_printf fclean
	make -C libft fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re


