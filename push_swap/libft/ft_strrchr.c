/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:20:20 by hrandri2          #+#    #+#             */
/*   Updated: 2026/02/03 05:37:45 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		src_len;
	char	cast_c;

	if (!s)
		return (NULL);
	cast_c = (char)c;
	src_len = ft_strlen(s);
	if (cast_c == '\0')
		return ((char *)s + src_len);
	while (src_len >= 0)
	{
		if (s[src_len] == cast_c)
			return ((char *)s + src_len);
		src_len--;
	}
	return (NULL);
}
