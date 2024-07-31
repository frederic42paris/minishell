/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:48:12 by rrichard          #+#    #+#             */
/*   Updated: 2024/05/02 12:55:54 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	sub_len;

	i = 0;
	sub_len = 0;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (start > 0 && s[i])
	{
		i++;
		start--;
	}
	while (s[i] && sub_len < len)
	{
		dest[sub_len] = s[i];
		i++;
		sub_len++;
	}
	dest[sub_len] = '\0';
	return (dest);
}
