/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:45:32 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/31 14:13:12 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

//Locates the first occurrence in the string s1
//of any of the bytes in the string s2
char	*ft_strpbrk(const char *s1, const char *s2)
{
	const char	*scanp;
	const char	*s1_temp;
	char		c;
	char		sc;

	s1_temp = s1;
	c = *s1_temp;
	while (c != 0)
	{
		scanp = s2;
		sc = *scanp;
		while (sc != 0)
		{
			if (sc == c)
				return ((char *)(s1_temp));
			scanp++;
			sc = *scanp;
		}
		s1_temp++;
		c = *s1_temp;
	}
	return (NULL);
}
