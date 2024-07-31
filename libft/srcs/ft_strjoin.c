/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:23:48 by rrichard          #+#    #+#             */
/*   Updated: 2024/02/06 15:52:34 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	len1 = 0;
	len2 = 0;
	while (s1[len1])
	{
		s[len1] = s1[len1];
		len1++;
	}
	while (s2[len2])
	{
		s[len1] = s2[len2++];
		len1++;
	}
	s[len1] = '\0';
	return (s);
}
