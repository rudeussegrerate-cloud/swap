/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 07:42:12 by hrandri2          #+#    #+#             */
/*   Updated: 2026/02/07 05:53:37 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_string = malloc((s1_len + s2_len) * sizeof(char) + 1);
	if (new_string == NULL)
		return (NULL);
	while (i < s1_len)
	{
		new_string[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
		new_string[i++] = s2[j++];
	new_string[i] = '\0';
	return (new_string);
}
