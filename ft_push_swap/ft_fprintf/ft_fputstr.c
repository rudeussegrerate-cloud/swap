/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:39:07 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:30 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fputstr(int fd, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write (fd, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		ft_fputchar(fd, str[i]);
		i++;
	}
	return (i);
}
