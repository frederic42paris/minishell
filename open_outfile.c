/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:38:41 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/01 16:49:08 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outfile_exist_v2(char *string)
{
	if (access(string, F_OK) == -1)
	{
		return (0);
	}
	return (1);
}

int	outfile_rights_v2(char *string)
{
	if (access(string, R_OK) == -1)
	{
		return (0);
	}
	return (1);
}

char	*find_last_outfile(t_redir *redir, int outfile_nb)
{
	int		i;

	i = 0;
	while (redir && i != outfile_nb)
	{
		if (ft_strncmp(redir->token, ">", 1) == 0)
			i++;
		if (i == outfile_nb)
			break ;
		redir = redir->next;
	}
	return (redir->name);
}

int	open_outfile(t_parse *par_list)
{
	char	*last_outfile;

	last_outfile = NULL;
	while (par_list)
	{
		if (par_list->redirection)
		{
			last_outfile = find_last_outfile(par_list->redirection, par_list->outfile_nb);
			printf("[%s]\n", last_outfile);
			if (outfile_exist_v2(last_outfile) == 1 && outfile_rights_v2(last_outfile) == 0)
				return (1);
			else
				par_list->fd_stdout = open(last_outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		par_list = par_list->next;
	}
	return (0);
}
