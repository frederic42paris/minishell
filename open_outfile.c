/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:38:41 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/03 16:27:42 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	outfile_exist_v2(char *string)
// {
// 	if (access(string, F_OK) == -1)
// 	{
// 		return (0);
// 	}
// 	return (1);
// }

// int	outfile_rights_v2(char *string)
// {
// 	if (access(string, R_OK) == -1)
// 	{
// 		return (0);
// 	}
// 	return (1);
// }

// char	*find_last_outfile(t_redir *redir, int outfile_nb)
// {
// 	int		i;

// 	i = 0;
// 	while (redir && i != outfile_nb)
// 	{
// 		if (ft_strncmp(redir->token, ">", 1) == 0)
// 			i++;
// 		if (i == outfile_nb)
// 			break ;
// 		redir = redir->next;
// 	}
// 	return (redir->name);
// }

int	open_outfile(t_parse *par_list, t_data *data)
{
	while (par_list->next)
		par_list = par_list->next;
	if (!par_list->redirection)
	{
		data->fd_stdout = STDOUT_FILENO;
		return (0);
	}
	while (par_list->redirection->next)
	{
		printf("par_list->redirection = %s\n", par_list->redirection->name);
		par_list->redirection = par_list->redirection->next;
	}
	if (par_list->redirection->type == 1)
	{
		if (!ft_strcmp(par_list->redirection->token, ">"))
			data->fd_stdout = open(par_list->redirection->name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (!ft_strcmp(par_list->redirection->token, ">>"))
			data->fd_stdout = open(par_list->redirection->name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	if (data->fd_stdout == 0)
		data->fd_stdout = STDOUT_FILENO;
	return (0);
}
