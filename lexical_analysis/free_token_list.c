/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:49:56 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/31 15:42:02 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token_list(t_token	**tok_list)
{
	t_token	*nextnode;

	while (*tok_list)
	{
		nextnode = (*tok_list)->next;
		free((*tok_list)->operator);
		free((*tok_list)->word);
		free(*tok_list);
		(*tok_list) = nextnode;
	}
}
