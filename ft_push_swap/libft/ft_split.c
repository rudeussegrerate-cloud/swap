/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:56:28 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/26 21:56:58 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	bol;

	i = 0;
	count = 0;
	bol = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!bol)
			{
				count++;
				bol = 1;
			}
		}
		else
			bol = 0;
		i++;
	}
	return (count);
}

static char	*copy(char const *s, int start, int len)
{
	char	*small;
	int		i;

	small = malloc(sizeof(char) * (len + 1));
	if (!small)
		return (NULL);
	i = 0;
	while (i < len)
	{
		small[i] = s[start + i];
		i++;
	}
	small[i] = '\0';
	return (small);
}

static void	**ft_free(char **big, int y)
{
	while (y-- > 0)
		free(big[y]);
	free(big);
	return (NULL);
}

static int	ft_get_word(char const *s, char c, int i, int *len)
{
	int	start;

	while (s[i] == c && s[i])
		i++;
	start = i;
	*len = 0;
	while (s[i] != c && s[i])
	{
		i++;
		(*len)++;
	}
	return (start);
}

char	**ft_split(char *str, char c)
{
	char	**big;
	int		k;
	int		i;
	int		y;

	if (!str)
		return (NULL);
	big = malloc(sizeof(char *) * (ft_count_words(str, c) + 1));
	if (!big)
		return (NULL);
	y = -1;
	i = 0;
	while (str[i])
	{
		i = ft_get_word(str, c, i, &k);
		if (k > 0 && ++y >= 0)
		{
			big[y] = copy(str, i, k);
			if (!big[y])
				return ((char **)ft_free(big, y));
		}
		i += k;
	}
	big[++y] = NULL;
	return (big);
}
