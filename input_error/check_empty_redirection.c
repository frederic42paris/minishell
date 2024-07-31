/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:18:01 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 15:29:20 by ftanon           ###   ########.fr       */
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
