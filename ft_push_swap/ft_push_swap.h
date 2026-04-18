/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:37:45 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/18 15:44:38 by tusandri         ###   ########.fr       */
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
# include "./ft_fprintf/ft_fprintf.h"

//*** principal structure ***
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

//*** handle count ***
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
	int	disorder_percent;
}	t_count;

//*** handle flags ***
typedef struct s_args
{
	char	*flag;
	char	**values;
	bool	free_values;
	bool	free_flag;
	bool	bench;
}	t_args;

//*** handle sort stack data */
typedef struct s_sort_data
{
	t_stack_node	**a;
	t_stack_node	**b;
	char			*flag;
	t_count			*count;
}	t_sort_data;

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

//*** rotate utils ***
void			finish_rotation(t_stack_node **s, t_stack_node *n, char c,
					t_count *count);
void			rotate_both(t_stack_node **a,
					t_stack_node **b,
					t_stack_node *cheapest_node,
					t_count *count);
void			reverse_rotate_both(t_stack_node **a,
					t_stack_node **b,
					t_stack_node *cheapest_node,
					t_count *count);

//*** flag management ***
void			adaptive_flag(int disorder_percent, t_stack_node **a,
					t_stack_node **b, t_count *count);
void			apply_sort_flag(char *arg, t_stack_node **a, t_stack_node **b,
					t_count *count);
char			*get_sort_flag(int argc, char **argv);
char			*repeat_flag(char **arg);
bool			check_flags(int argc, char **argv, t_args *args);
bool			has_bench_flag(int argc, char **argv);

//*** Medium sort utils ***
void			sort_index_array(int *arr, int len);
void			fill_array(t_stack_node *a, int *arr);
void			assign_final_index(t_stack_node *a);
void			update_targets(t_stack_node *cur, int pos, t_stack_node **t,
					int *p);
t_stack_node	*find_bucket_target(t_stack_node *a, int idx[2], bool *rra);
void			rotate_to_target(t_stack_node **a, t_stack_node *target,
					bool use_rra, t_count *count);
void			advance_bucket(int idx[2], int *pushed, int bkt);
void			push_buckets(t_stack_node **a, t_stack_node **b, int bkt,
					t_count *count);
void			move_back_fast(t_stack_node **a, t_stack_node **b,
					t_count *count);
void			move_back_very_slow(t_stack_node **a, t_stack_node **b,
					t_count *count);

//*** simple sort utils ***
int				cost_to_top(t_stack_node *stack, t_stack_node *node);
int				calculate_total_cost(t_stack_node *a, t_stack_node *b,
					t_stack_node *node);
t_stack_node	*find_cheapest_limited(t_stack_node *a, t_stack_node *b,
					int percent);
t_stack_node	*find_insert_position(t_stack_node *a, int value);

//*** Simple sort ***
void			tiny_sort(t_stack_node **a, t_count *count);
void			sort_small_a(t_stack_node **a, t_count *c, int len);
void			push_swap(t_stack_node **a, t_stack_node **b, t_count *count);
void			move_slow(t_stack_node **a, t_stack_node **b, t_count *count);
void			move_fast(t_stack_node **a, t_stack_node **b,
					t_count *count, int percent);

//*** Medium sort ***
void			medium_sort(t_stack_node **a, t_stack_node **b, t_count *count);

//*** Complex sort ***
void			radix_sort(t_stack_node **a, t_stack_node **b, t_count *count);
void			sort_five(t_stack_node **a, t_stack_node **b, t_count *count);
void			bring_to_top(t_stack_node **a, t_stack_node *node,
					t_count *count);

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

//*** bench utils ***
float			compute_disorder(t_stack_node *a);
void			bench_mode(t_stack_node **a, double disorder_percent,
					char *flag, t_count *count);
void			print_count(t_count *count);

//*** Flags utils ***
char			**extract_values(char **split_args, char **flag, bool *bench);
bool			is_flag_argument(char *arg);

#endif
