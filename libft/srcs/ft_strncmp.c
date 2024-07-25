/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:27:08 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/30 15:42:35 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

//Compares the two string s1 and s2 at most n bytes
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	str1;
	unsigned char	str2;

	i = 0;
	while (i < n)
	{
		str1 = (unsigned char)s1[i];
		str2 = (unsigned char)s2[i];
		if (str1 != str2)
			return (str1 - str2);
		if (str1 == '\0')
			return (0);
		i++;
	}
	return (0);
}
