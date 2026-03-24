/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 23:16:13 by hrandri2          #+#    #+#             */
/*   Updated: 2026/02/09 11:02:02 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_putunbr(unsigned int nbr)
{
	long	digit;

	digit = 0;
	if (nbr / 10 != 0)
		ft_putunbr(nbr / 10);
	digit = (nbr % 10) + '0';
	ft_putchar (digit);
	return (ft_count_len(nbr));
}
