/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 23:35:56 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/23 22:44:21 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void bench_mode(double disorder_percent, char *flag, t_count *count)
{
    disorder_percent = disorder_percent * 100;
    ft_printf("[bench] disorder: %.2f%%\n", disorder_percent);
    ft_printf("[bench] strategy: %s", flag);
    if (ft_strcmp(flag, "--simple") == 0)
        ft_printf(" / O(n^2)\n");
    else if (ft_strcmp(flag, "--medium") == 0)
        ft_printf(" / O(nVn)\n");
    else if (ft_strcmp(flag, "--complex") == 0)
        ft_printf(" / O(nlogn)\n");
    else if (ft_strcmp(flag, "--adaptive") == 0)
    {
        if (disorder_percent < 20.0)
            ft_printf(" / O(n^2)\n");
        else if (disorder_percent < 50.0)
            ft_printf(" / O(nVn)\n");
        else
            ft_printf(" / O(nlogn)\n");
    }
    print_count(count);
}
