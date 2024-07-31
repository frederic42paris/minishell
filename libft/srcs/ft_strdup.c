/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:11:24 by rrichard          #+#    #+#             */
/*   Updated: 2024/02/06 15:54:31 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

//Returns a pointer to a new string which is
//a duplicate of the string s.
char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	i = 0;
	if (dest == NULL)
		return (0);
	else
	{
		while (s1[i])
		{
			dest[i] = s1[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (dest);
}
