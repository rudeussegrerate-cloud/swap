/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:56:28 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/18 20:38:24 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
static int	count_words(char *str, char separator)
{
	int		count;
	bool	inside_word;

	count = 0;
	while (*str)
	{
		inside_word = false;
		while (*str == separator && *str)
			++str;
		while (*str != separator && *str)
		{
			if (!inside_word)
			{
				++count;
				inside_word = true;
			}
			++str;
		}
	}
	return (count);
}

static char	*get_next_word(char *str, char separator)
{
	static int	cursor = 0;
	char		*next_str;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (str[cursor] == separator)
		++cursor;
	while ((str[cursor + len] != separator) && str[cursor + len])
		++len;
	next_str = malloc((size_t)len * sizeof(char) + 1);
	if (NULL == next_str)
		return (NULL);
	while ((str[cursor] != separator) && str[cursor])
		next_str[i++] = str[cursor++];
	next_str[i] = '\0';
	return (next_str);
}

char	**ft_split(char *str, char separator)
{
	int		words_number;
	char	**vector_strings;
	int		i;

	i = 0;
	words_number = count_words(str, separator);
	if (!words_number)
		exit(1);
	vector_strings = malloc(sizeof(char *) * (size_t)(words_number + 2));
	if (NULL == vector_strings)
		return (NULL);
	while (words_number-- >= 0)
	{
		if (0 == i)
		{
			vector_strings[i] = malloc(sizeof(char));
			if (NULL == vector_strings[i])
				return (NULL);
			vector_strings[i++][0] = '\0';
			continue ;
		}
		vector_strings[i++] = get_next_word(str, separator);
	}
	vector_strings[i] = NULL;
	return (vector_strings);
} */

// #include <stdio.h>
// int main(void)
// {
// 	char *tab = "hello bonjour lolo";
// 	char **tab1 = (ft_split(tab, ' '));
// 	int i = 0;
// 	while (i < 4)
// 	{
// 		printf("%s\n", tab1[i]);
// 		i++;
// 	}
	
// }


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
/*
#include <stdio.h>
int main(void)
{
	char *tab = "hello bonjour lolo";
	char **tab1 = (ft_split(tab, ' '));
	int i = 0;
	while (i < 3)
	{
		printf("%s\n", tab1[i]);
		i++;
	}
	
}*/