/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_min.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:52:07 by hrandri2          #+#    #+#             */
/*   Updated: 2026/02/12 11:11:29 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa_min(unsigned int nbr)
{
	char	*base;
	int		len;

	len = 0;
	base = "0123456789abcdef";
	if ((nbr / 16) != 0)
		len = ft_hexa_min((nbr / 16));
	len += write(1, &base[(nbr % 16)], 1);
	return (len);
}
