/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:17:15 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/15 09:24:44 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *restrict dest, const char *restrict src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	dest_len = 0;
	src_len = 0;
	if (!size)
		return (ft_strlen(src));
	while (dest[dest_len])
		dest_len++;
	while (src[src_len])
		src_len++;
	if (size <= dest_len)
		return (src_len + size);
	i = 0;
	while (src[i] && i < size - dest_len - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

/* #include <stdio.h>
int	main(int ac, char **av)
{
	if (ac == 4)
	{
		printf("%zu\n", ft_strlcat(av[1], av[2], atoi(av[3])));
	}
	return (0);
} */
