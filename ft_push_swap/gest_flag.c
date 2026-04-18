/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 20:23:01 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/18 15:22:48 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	adaptive_flag(int disorder_percent, t_stack_node **a,
				t_stack_node **b, t_count *count)
{
	if (disorder_percent < 20 || stack_len(*a) <= 5)
		push_swap(a, b, count);
	else if (disorder_percent >= 20 && disorder_percent < 50)
		medium_sort(a, b, count);
	else
		radix_sort(a, b, count);
}

void	apply_sort_flag(char *arg, t_stack_node **a, t_stack_node **b,
			t_count *count)
{
	if (!arg || ft_strcmp(arg, "--adaptive") == 0
		|| ft_strcmp(arg, "--bench") == 0)
		adaptive_flag(count->disorder_percent, a, b, count);
	else if (ft_strcmp(arg, "--simple") == 0)
		push_swap(a, b, count);
	else if (ft_strcmp(arg, "--medium") == 0)
		medium_sort(a, b, count);
	else if (ft_strcmp(arg, "--complex") == 0)
		radix_sort(a, b, count);
	else
		(write(2, "Error\n", 6), exit(1));
}

char	*get_sort_flag(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "--", 2) == 0
			&& ft_strcmp(argv[i], "--bench") != 0)
			return (argv[i]);
		i++;
	}
	return (NULL);
}

char	*repeat_flag(char **arg)
{
	int		i;
	int		j;
	int		flags;
	char	*f[4];

	f[0] = "--simple";
	f[1] = "--medium";
	f[2] = "--complex";
	f[3] = "--adaptive";
	flags = 0;
	i = -1;
	while (arg[++i])
	{
		j = -1;
		while (++j < 4)
			if (ft_strcmp(f[j], arg[i]) == 0 && ++flags > 1)
				return (arg[i]);
	}
	return (NULL);
}

bool	is_flag_argument(char *arg)
{
	if (!arg)
		return (false);
	if (ft_strncmp(arg, "--", 2) != 0)
		return (false);
	if (ft_strchr(arg, ' '))
		return (false);
	return (true);
}
