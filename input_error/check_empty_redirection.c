/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:18:01 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/08 17:41:18 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_empty_redirection(t_token *tok_list)
{
	while (tok_list)
	{
		if (tok_list->operator && is_bracket(tok_list->operator[0]))
		{
			tok_list = tok_list->next;
			if (!tok_list
				|| (tok_list->operator && tok_list->operator[0] == '|'))
			{
				printf("Error : invalid cmd\n");
				return (1);
			}
		}
		if (tok_list)
			tok_list = tok_list->next;
	}
	return (0);
}

char	*init_ope_char(t_token *tok_list)
{
	char	*str;

	str = NULL;
	if (tok_list && tok_list->operator)
		str = tok_list->operator;
	return (str);
}

int	check_empty_cmd(t_token *tok_list)
{
	char	*str;

	str = init_ope_char(tok_list);
	if (tok_list)
		tok_list = tok_list->next;
	while (tok_list)
	{
		if (tok_list->operator)
		{
			if (str)
			{
				if (ft_strncmp(str, "|", 1) == 0
					&& ft_strncmp(tok_list->operator, "|", 1) == 0)
				{
					printf("Error : invalid cmd\n");
					return (1);
				}
			}
			else
				str = tok_list->operator;
		}
		if (tok_list)
			tok_list = tok_list->next;
	}
	return (0);
}