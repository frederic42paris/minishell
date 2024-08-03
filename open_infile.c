/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:38:41 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/03 16:12:49 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	infile_exist_v2(char *string)
// {
// 	if (access(string, F_OK) == -1)
// 	{
// 		return (0);
// 	}
// 	return (1);
// }

// int	infile_rights_v2(char *string)
// {
// 	if (access(string, R_OK) == -1)
// 	{
// 		return (0);
// 	}
// 	return (1);
// }

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

int	open_infile(t_parse *par_list, t_data *data)
{
	char	*last_infile;

	last_infile = NULL;
	if (par_list->redirection)
	{
		if (par_list->redirection->type == 0)
		{		
			last_infile = find_last_infile(par_list->redirection, par_list->infile_nb);
			printf(" TEST : [%s]\n", last_infile);
			data->fd_stdin = open(last_infile, O_RDONLY);
			if (data->fd_stdin < 0)
				return (perror(last_infile), 1);
		}
	}
	return (0);
}
