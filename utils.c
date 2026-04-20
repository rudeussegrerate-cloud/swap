#include "push_swap.h"

void	ft_putstr_fd(const char *s, int fd)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(fd, s, len);
}

t_stack	*new_node(int value)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = -1;
	node->next = NULL;
	return (node);
}

void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

int	stack_size(t_stack *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

/*
** Assigns a rank (0 = smallest) to each node's index field.
** Uses O(n^2) comparison: counts how many nodes have a smaller value.
*/
void	assign_index(t_stack *stack)
{
	t_stack	*curr;
	t_stack	*check;

	curr = stack;
	while (curr)
	{
		curr->index = 0;
		check = stack;
		while (check)
		{
			if (check->value < curr->value)
				curr->index++;
			check = check->next;
		}
		curr = curr->next;
	}
}

/*
** Returns the 0-based position of the element with the maximum index.
*/
int	find_max_pos(t_stack *stack)
{
	int		pos;
	int		max_pos;
	int		max_idx;
	t_stack	*curr;

	pos = 0;
	max_pos = 0;
	max_idx = -1;
	curr = stack;
	while (curr)
	{
		if (curr->index > max_idx)
		{
			max_idx = curr->index;
			max_pos = pos;
		}
		pos++;
		curr = curr->next;
	}
	return (max_pos);
}
