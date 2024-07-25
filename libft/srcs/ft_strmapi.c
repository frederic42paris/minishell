/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:24:05 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/15 09:24:44 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* 
#include <stdio.h>
char uppercase(unsigned int index, char c)
{
	(void)index;
    if (c >= 'a' && c <= 'z')
        return c - 32; // Convert to uppercase
    return c;
}

int main(void)
{
    char *testStrings[] = {"hello", "world", "", "C programming", NULL};
    char *result;

    for (int i = 0; testStrings[i] != NULL; i++)
	{
        printf("Original string: %s\n", testStrings[i]);
        result = ft_strmapi(testStrings[i], uppercase);
        if (result != NULL)
		{
            printf("Transformed string: %s\n", result);
            free(result);
        } 
		else
            printf("Transformed string: (null)\n");
        printf("\n");
    }

    return 0;
} */
