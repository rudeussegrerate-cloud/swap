/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 23:35:56 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/01 20:27:49 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static char	*clean_flag_name(char *flag)
{
	if (!flag)
		return ("adaptive");
	if (ft_strncmp(flag, "--", 2) == 0)
		return (flag + 2);
	return (flag);
}

void	bench_mode(double disorder_percent, char *flag, t_count *count)
{
	char	*name;

	disorder_percent = disorder_percent * 100;
	name = clean_flag_name(flag);
	ft_fprintf(2, "[bench] disorder: %.2f%%\n", disorder_percent);
	ft_fprintf(2, "[bench] strategy: %s", name);
	if (ft_strcmp(name, "simple") == 0)
		ft_fprintf(2, " / O(n^2)\n");
	else if (ft_strcmp(name, "medium") == 0)
		ft_fprintf(2, " / O(n√n)\n");
	else if (ft_strcmp(name, "complex") == 0)
		ft_fprintf(2, " / O(n log n)\n");
	else if (ft_strcmp(name, "adaptive") == 0)
	{
		if (disorder_percent < 20.0)
			ft_fprintf(2, " / O(n^2)\n");
		else if (disorder_percent < 50.0)
			ft_fprintf(2, " / O(n√n)\n");
		else
			ft_fprintf(2, " / O(n log n)\n");
	}
	print_count(count);
}
