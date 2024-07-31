/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:37:33 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/15 09:24:44 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*str2;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	str = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	if (str2 < str)
		while (len--)
			str[len] = str2[len];
	else
	{
		while (i < len)
		{
			str[i] = str2[i];
			i++;
		}
	}
	return (dst);
}
