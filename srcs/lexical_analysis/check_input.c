/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:37:19 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/23 15:52:52 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_double_quote_check(char c)
{
	if (c != '"' && c != '\0')
		return (1);
	else
		return (0);
}

int	not_single_quote_check(char c)
{
	if (c != 39 && c != '\0')
		return (1);
	else
		return (0);
}

// only handle special characters mentionned in the subject
int	check_input(char const *str)
{
	int	i;

	i = 0;
	// if (!(str[i] >= 97 && str[i] <= 122) && str[i] != '>' && str[i] != '<' && str[i] != '.' && str[i] != '/' && str[i] != ' ' && str[i] != 39 && str[i] != '"' && str[i] != '$')
	// {
	// 	printf("Error : Invalid cmd\n");
	// 	return (1);
	// }
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			while (not_double_quote_check(str[i]))
				i++;
			if (str[i] == '\0')
			{
				printf("Error : Double quotes unclosed\n");
				return (1);
			}
		}
		else if (str[i] == 39)
		{
			i++;
			while (not_single_quote_check(str[i]))
				i++;
			if (str[i] == '\0')
			{
				printf("Error : Single quotes unclosed\n");
				return (1);
			}
		}
		i++;
	}
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
