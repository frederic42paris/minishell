/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:55:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/23 15:53:32 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outfile_exist(char *string)
{
	if (access(string, F_OK) == -1)
		return (0);
	return (1);
}

void	check_outfile(t_redir *redir_list)
{
	while (redir_list)
	{
		if (redir_list->type == 1)
		{
			if (redir_list->name != NULL)
			{
				redir_list->exist = outfile_exist(redir_list->name);
				if (redir_list->exist == 1 && access(redir_list->name,
						W_OK) == -1)
					redir_list->access = 0;
				else
					redir_list->access = 1;
			}
		}
		redir_list = redir_list->next;
	}
}
