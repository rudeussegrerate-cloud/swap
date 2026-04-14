/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 23:16:13 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:46 by tusandri         ###   ########.fr       */
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
