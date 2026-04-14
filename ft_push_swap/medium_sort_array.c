/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 01:12:29 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/08 01:40:37 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	sort_index_array(int *arr, int len)
{
	int	i;
	int	j;
	int	min;
	int	tmp;

	i = 0;
	while (i < len - 1)
	{
		min = i;
		j = i + 1;
		while (j < len)
		{
			if (arr[j] < arr[min])
				min = j;
			j++;
		}
		if (min != i)
		{
			tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
		}
		i++;
	}
}

void	fill_array(t_stack_node *a, int *arr)
{
	int	idx;

	idx = 0;
	while (a)
	{
		arr[idx++] = a->value;
		a = a->next;
	}
}

void	assign_final_index(t_stack_node *a)
{
	int				len;
	int				*arr;
	t_stack_node	*cur;

	len = stack_len(a);
	if (!len)
		return ;
	arr = malloc(sizeof(int) * len);
	if (!arr)
		return ;
	fill_array(a, arr);
	sort_index_array(arr, len);
	cur = a;
	while (cur)
	{
		cur->final_index = 0;
		while (cur->final_index < len && cur->value != arr[cur->final_index])
			cur->final_index++;
		cur = cur->next;
	}
	free(arr);
}
