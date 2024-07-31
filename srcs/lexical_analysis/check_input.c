/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:37:19 by ftanon            #+#    #+#             */
<<<<<<<< HEAD:srcs/lexical_analysis/check_input.c
/*   Updated: 2024/07/23 15:52:52 by rrichard         ###   ########.fr       */
========
/*   Updated: 2024/07/30 14:23:40 by ftanon           ###   ########.fr       */
>>>>>>>> 16939a04bd97ccc16f423952e771f611d521774d:input_error/check_input.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_string(char const *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	check_quote_unclosed(char const *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == 39)
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i] != '\0')
				i++;
			if (str[i] == '\0')
			{
				if (c == '"')
					printf("Error : Double quotes unclosed\n");
				else if (c == 39)
					printf("Error : Single quotes unclosed\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_input(char const *str)
{
	if (check_quote_unclosed(str) == 1)
		return (1);
	if (check_empty_string(str) == 1)
		return (1);
	return (0);
}
