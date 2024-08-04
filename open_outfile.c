/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:38:41 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/04 12:10:50 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		par_list->redirection = par_list->redirection->next;
	if (par_list->redirection->type == 1)
	{
		if (!ft_strcmp(par_list->redirection->token, ">"))
			data->fd_stdout = open(par_list->redirection->name,
					O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (!ft_strcmp(par_list->redirection->token, ">>"))
			data->fd_stdout = open(par_list->redirection->name,
					O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (data->fd_stdout < 0)
			return (perror(par_list->redirection->name), 1);
	}
	if (data->fd_stdout == 0)
		data->fd_stdout = STDOUT_FILENO;
	return (0);
}
