#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

/* Stack operations */
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);

/* Utils */
t_stack	*new_node(int value);
void	free_stack(t_stack **stack);
int		stack_size(t_stack *stack);
int		is_sorted(t_stack *stack);
void	assign_index(t_stack *stack);
int		find_max_pos(t_stack *stack);
void	ft_putstr_fd(const char *s, int fd);

/* Sort */
void	sort_stack(t_stack **a, t_stack **b);

/* Parse */
t_stack	*parse_args(int argc, char **argv);
void	error_exit(t_stack **a);
int		ft_atoi_safe(const char *s, long *result);

#endif
