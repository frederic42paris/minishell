/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:44:35 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/15 09:24:44 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*to_find)
		return ((char *)str);
	if (!len)
		return (NULL);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && i + j < len)
		{
			if (!to_find[j + 1])
				return ((char *)&str[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/* #include <stdio.h>
int	main(int ac, char **av)
{
	if (ac == 4)
		printf("%s\n", ft_strnstr(av[1], av[2], atoi(av[3])));
	return (0);
} */
