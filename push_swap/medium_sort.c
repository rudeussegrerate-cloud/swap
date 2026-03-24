/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:00:53 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/22 07:28:36 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void sort_index_array(int *arr, int len)
{
    int i;
    int j;
    int min;
    int tmp;

    for (i = 0; i < len - 1; ++i)
    {
        min = i;
        for (j = i + 1; j < len; ++j)
            if (arr[j] < arr[min])
                min = j;
        if (min != i)
        {
            tmp = arr[i];
            arr[i] = arr[min];
            arr[min] = tmp;
        }
    }
}

static void assign_final_index(t_stack_node *a)
{
    int len; int *arr; int idx; t_stack_node *cur;

    len = stack_len(a);
    if (!len)
        return ;
    arr = malloc(sizeof(int) * len);
    if (!arr)
        return ;
    idx = 0;
    for (cur = a; cur; cur = cur->next)
        arr[idx++] = cur->value;
    sort_index_array(arr, len);
    for (cur = a; cur; cur = cur->next)
    {
        idx = 0;
        while (idx < len && cur->value != arr[idx])
            idx++;
        cur->final_index = idx;
    }
    free(arr);
}

static t_stack_node *find_bucket_target(t_stack_node *a,
    int min_idx,
    int max_idx,
    bool *use_rra)
{
    int len = stack_len(a), pos = 0, first_pos = 0, last_pos = 0;
    t_stack_node *first = NULL, *last = NULL, *cur = a;
    while (cur)
    {
        if (cur->final_index >= min_idx && cur->final_index <= max_idx)
        {
            if (!first){first = cur; first_pos = pos;}
            last = cur; last_pos = pos;
        }
        cur = cur->next; pos++;
    }
    if (!first) return (NULL);
    if (first_pos <= len - last_pos){*use_rra = false; return (first);}
    *use_rra = true;
    return (last);
}

static void move_back_from_b(t_stack_node **a, t_stack_node **b, t_count *count)
{
    t_stack_node *cheapest;

    while (*b)
    {
        init_nodes(*a, *b);
        cheapest = return_cheapest(*b);
        if (!cheapest)
            break ;
        if (cheapest->above_median
            && cheapest->target_node->above_median)
            while (*a != cheapest->target_node && *b != cheapest)
                rr(a, b, count);
        else if (!cheapest->above_median
            && !cheapest->target_node->above_median)
            while (*a != cheapest->target_node && *b != cheapest)
                rrr(a, b, count);
        finish_rotation(b, cheapest, 'b', count);
        finish_rotation(a, cheapest->target_node, 'a', count);
        pa(a, b, count);
    }
}

void medium_sort(t_stack_node **a, t_stack_node **b, t_count *count)
{
    int len = stack_len(*a);
    int bucket_size = (len / 5) + 1;
    int min_idx = 0;
    int max_idx = bucket_size - 1;
    int pushed = 0;
    bool use_rra;
    t_stack_node *target;

    assign_final_index(*a);
    while (stack_len(*a) > 3)
    {
        target = find_bucket_target(*a, min_idx, max_idx, &use_rra);
        if (!target)
        {
            min_idx += bucket_size;
            max_idx += bucket_size;
            continue ;
        }
        while (*a != target)
            (use_rra ? rra(a, count) : ra(a, count));
        pb(b, a, count);
        if ((*b)->final_index < min_idx + (bucket_size / 2))
            rb(b, count);
        if (++pushed >= bucket_size)
        {
            min_idx += bucket_size;
            max_idx += bucket_size;
            pushed = 0;
        }
    }
    tiny_sort(a, count);
    move_back_from_b(a, b, count);
    set_current_position(*a);
    target = find_smallest(*a);
    if (target->above_median)
        while (*a != target)
            ra(a, count);
    else
        while (*a != target)
            rra(a, count);
}
