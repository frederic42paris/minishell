/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:47:31 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/15 09:24:44 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_isinset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*res;

	start = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (start < end && ft_isinset(s1[start], set))
		++start;
	while (end > start && ft_isinset(s1[end - 1], set))
		--end;
	res = malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	while (i < end - start)
	{
		res[i] = s1[start + i];
		++i;
	}
	res[i] = '\0';
	return (res);
}

/* int		main(int ac, char **av)
{
	if (ac == 3)
	{
		printf("%s\n", ft_strtrim(av[1], av[2]));
	}
	return (0);
} */
