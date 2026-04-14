/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:45:09 by hrandri2          #+#    #+#             */
/*   Updated: 2026/02/04 18:50:59 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nbr;
	int	sign;
	int	count;

	nbr = 0;
	sign = 1;
	i = 0;
	count = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		count++;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
		nbr = nbr * 10 + (nptr[i++] - 48);
	if (count > 1)
		return (0);
	return (nbr * sign);
}
