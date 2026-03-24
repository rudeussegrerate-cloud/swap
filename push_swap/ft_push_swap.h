/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:37:45 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/23 23:02:51 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stddef.h>
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"

typedef struct s_stack_node
{
	int					value;
	int					current_position;
	int					final_index;
	int					push_price;
	bool				above_median;
	bool				cheapest;
	struct s_stack_node	*target_node;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}				t_stack_node;	

typedef struct s_count
{
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
}	t_count;

typedef struct s_args
{
	char	*flag;
	char	**values;
	bool	free_values;
}t_args;

//*** Handle errors-free ***
void			free_matrix(char **argv);
void			error_free(t_stack_node **a, char **argv, bool flag_argc_2);
void			free_stack(t_stack_node **stack);
int				error_repetition(t_stack_node *a, int nbr);
int				error_syntax(char *str_nbr);

//*** Stack creation ***
void			stack_init(t_stack_node **a, char **argv, bool flag_argc_2);
void			init_nodes(t_stack_node *a, t_stack_node *b);
void			set_current_position(t_stack_node *stack);
void			set_price(t_stack_node *a, t_stack_node *b);
void			set_cheapest(t_stack_node *b);

//*** linked list utils ***
void			append_node(t_stack_node **stack, int nbr);
t_stack_node	*find_last_node(t_stack_node *head);
t_stack_node	*find_smallest(t_stack_node *stack);
t_stack_node	*return_cheapest(t_stack_node *stack);
bool			stack_sorted(t_stack_node *stack);
int				stack_len(t_stack_node *stack);
void			finish_rotation(t_stack_node **s, t_stack_node *n, char c, t_count *count);

//*** Simple sort ***
void		tiny_sort(t_stack_node **a, t_count *count);
void		handle_five(t_stack_node **a, t_stack_node **b, t_count *count);
void		push_swap(t_stack_node **a, t_stack_node **b, t_count *count);

//*** Medium sort ***
void		medium_sort(t_stack_node **a, t_stack_node **b, t_count *count);

//*** Complex sort ***
void		radix_sort(t_stack_node **a, t_stack_node **b, t_count *count);

//*** Commands ***
void			sa(t_stack_node **a, t_count *count);
void			sb(t_stack_node **b, t_count *count);
void			ss(t_stack_node **a, t_stack_node **b, t_count *count);
void			ra(t_stack_node **a, t_count *count);
void			rb(t_stack_node **b, t_count *count);
void			rr(t_stack_node **a, t_stack_node **b, t_count *count);
void			rra(t_stack_node **a, t_count *count);
void			rrb(t_stack_node **b, t_count *count);
void			rrr(t_stack_node **a, t_stack_node **b, t_count *count);
void			pa(t_stack_node **a, t_stack_node **b, t_count *count);
void			pb(t_stack_node **b, t_stack_node **a, t_count *count);

float			compute_disorder(t_stack_node *a);
void			bench_mode(double disorder_percent, char *flag, t_count *count);
void			print_count(t_count *count);
#endif
