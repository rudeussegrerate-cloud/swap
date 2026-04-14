/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_maj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:35:49 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:39 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa_maj(unsigned int nbr)
{
	char	*base;
	int		len;

	len = 0;
	base = "0123456789ABCDEF";
	if ((nbr / 16) != 0)
		len = ft_hexa_maj((nbr / 16));
	len += write(1, &base[(nbr % 16)], 1);
	return (len);
}
