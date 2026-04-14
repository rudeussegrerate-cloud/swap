/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 08:43:20 by hrandri2          #+#    #+#             */
/*   Updated: 2026/02/04 18:34:01 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cast_s;
	size_t			i;
	unsigned char	cast_c;

	cast_c = (unsigned char)c;
	cast_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (cast_s[i] == cast_c)
			return ((void *)(cast_s + i));
		i++;
	}
	return (NULL);
}
