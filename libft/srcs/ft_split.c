/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:12:18 by rrichard          #+#    #+#             */
/*   Updated: 2024/05/02 12:55:34 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_count_words(char const *str, char charset)
{
	size_t	i;
	size_t	words_count;
	size_t	in_words;

	i = 0;
	words_count = 0;
	in_words = 0;
	while (str[i])
	{
		if (str[i] != charset && !in_words)
		{
			words_count++;
			in_words = 1;
		}
		else if (str[i] == charset)
			in_words = 0;
		i++;
	}
	return (words_count);
}

static int	ft_len_words(char const *str, char charset, size_t start)
{
	size_t	len_words;

	len_words = 0;
	while (str[start] && str[start] != charset)
	{
		start++;
		len_words++;
	}
	return (len_words);
}

char	**dosplit(char const *s, char **split, char c)
{
	size_t	i;
	size_t	line;
	size_t	j;

	i = 0;
	line = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			split[line] = malloc(sizeof(char) * (ft_len_words(s, c, i) + 1));
			if (!split[line])
				return (NULL);
			j = 0;
			while (s[i] && s[i] != c)
				split[line][j++] = s[i++];
			split[line++][j] = '\0';
		}
		else
			i++;
	}
	split[line] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!split)
		return (NULL);
	split = dosplit(s, split, c);
	return (split);
}
