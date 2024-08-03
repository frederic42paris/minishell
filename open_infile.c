/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:38:41 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/01 16:49:15 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_exist_v2(char *string)
{
	if (access(string, F_OK) == -1)
	{
		return (0);
	}
	return (1);
}

int	infile_rights_v2(char *string)
{
	if (access(string, R_OK) == -1)
	{
		return (0);
	}
	return (1);
}

char	*find_last_infile(t_redir *redir, int infile_nb)
{
	int		i;

	i = 0;
	while (redir && i != infile_nb)
	{
		if (ft_strncmp(redir->token, "<", 1) == 0)
			i++;
		if (i == infile_nb)
			break ;
		redir = redir->next;
	}
	return (redir->name);
}

int	open_infile(t_parse *par_list)
{
	char	*last_infile;

	last_infile = NULL;
	while (par_list)
	{
		if (par_list->redirection)
		{
			last_infile = find_last_infile(par_list->redirection, par_list->infile_nb);
			printf("[%s]\n", last_infile);
			if (infile_exist_v2(last_infile) == 0)
				par_list->fd_stdin = open(last_infile, O_CREAT, 0644);
			else if (infile_exist_v2(last_infile) == 1 && infile_rights_v2(last_infile) == 0)
				return (1);
			else
				par_list->fd_stdin = open(last_infile, O_RDONLY);
		}
		par_list = par_list->next;
	}
	return (0);
}
