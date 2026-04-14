NAME = push_swap
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = main.c error_free.c push_command.c simple_sort.c \
		push_swap_init.c reverse_rotate_command.c rotate_command.c \
		stack_init.c stack_utils.c swap_command.c tiny_sort.c disorder.c \
		medium_sort.c complex_sort.c bench.c operation.c rotate_utils.c \
		gest_flag.c medium_sort_array.c medium_target.c simple_find_cost.c \
		medium_move.c simple_move.c split_extract_values.c gest_flag_2.c
OBJS = $(SRCS:.c=.o)

HEADERS = push_swap.h

LIBFTFPRINTF = ft_fprintf/libftfprintf.a
LIBFT = libft/libft.a

all : $(NAME)

$(LIBFTFPRINTF):
	make -C ft_fprintf
$(LIBFT):
	make -C libft

$(NAME) : $(OBJS) $(LIBFTFPRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L./ft_fprintf -lftfprintf -L./libft -lft -o $(NAME)

clean :
	rm -f $(OBJS)
	rm -f $(LIBFTFPRINTF)
	rm -f $(LIBFT)


fclean : clean
	make -C ft_fprintf fclean
	make -C libft fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
