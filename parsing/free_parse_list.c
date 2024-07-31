/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:47:54 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/31 15:42:02 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redir_list(t_redir	**redir_list)
{
	t_redir	*nextnode;

	while (*redir_list)
	{
		nextnode = (*redir_list)->next;
		free((*redir_list)->token);
		free((*redir_list)->name);
		free(*redir_list);
		(*redir_list) = nextnode;
	}
}

void	free_parse_list(t_parse	**par_list)
{
	t_parse	*nextnode;

	while (*par_list)
	{
		nextnode = (*par_list)->next;
		free_redir_list(&(*par_list)->redirection);
		free_array((*par_list)->cmd_array);
		free((*par_list)->path);
		free(*par_list);
		(*par_list) = nextnode;
	}
}
