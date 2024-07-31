/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:49:32 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/15 09:24:44 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		if (str[i] == (char)c)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
