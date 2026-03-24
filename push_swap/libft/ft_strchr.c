/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:36:21 by hrandri2          #+#    #+#             */
/*   Updated: 2026/02/04 18:13:11 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	cast_c;

	cast_c = (char)c;
	while (*s)
	{
		if (*s == cast_c)
			return ((char *)s);
		s++;
	}
	if (cast_c == '\0')
		return ((char *)s);
	return (NULL);
}
