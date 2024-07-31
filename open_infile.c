/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:38:41 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/31 18:35:01 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_parse *par_list)
{
	int	i;

	while (par_list)
	{
		if (par_list->redirection)
		{
			i = 0;
			while (par_list->redirection && i != par_list->infile_nb)
			{
				if (ft_strncmp(par_list->redirection->token, "<", 1) == 0)
					i++;
				if (i == par_list->infile_nb)
					break ;
				par_list->redirection = par_list->redirection->next;
			}
			if (par_list->redirection->exist == 0)
				par_list->fd_stdin = open(par_list->redirection->name, O_CREAT, 0644);
			else if (par_list->redirection->exist == 1 && par_list->redirection->access == 0)
				return (1);
			else
				par_list->fd_stdin = open(par_list->redirection->name, O_RDONLY);
		}
		par_list = par_list->next;
	}
	return (0);
}
