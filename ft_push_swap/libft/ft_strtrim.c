/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 08:59:59 by hrandri2          #+#    #+#             */
/*   Updated: 2026/01/31 11:59:01 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str_trimed;
	size_t	i;
	size_t	total_len;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (start == end)
		return (ft_strdup(""));
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	total_len = end - start;
	str_trimed = malloc(total_len * sizeof(char) + 1);
	if (!str_trimed)
		return (NULL);
	while (i < total_len)
		str_trimed[i++] = s1[start++];
	str_trimed[i] = '\0';
	return (str_trimed);
}
