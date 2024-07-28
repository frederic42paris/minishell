/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:54:51 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 15:28:57 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_exist(char *string)
{
	if (access(string, F_OK) == -1)
	{
		return (0);
	}
	return (1);
}

int	infile_rights(char *string)
{
	if (access(string, R_OK) == -1)
	{
		return (0);
	}
	return (1);
}

void	check_infile(t_redir *redir_list)
{
	while (redir_list)
	{
		if (redir_list->type == 0)
		{
			if (redir_list->name != NULL
				&& ft_strlen(redir_list->token) == 1)
			{
				redir_list->exist = infile_exist(redir_list->name);
				if (redir_list->exist == 1)
					redir_list->access = infile_rights(redir_list->name);
			}
		}
		redir_list = redir_list->next;
	}
}
