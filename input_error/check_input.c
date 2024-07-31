/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:37:19 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/31 16:11:56 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
