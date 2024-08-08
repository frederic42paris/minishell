/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:38:41 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/08 17:32:08 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_outfile(t_parse *par_list, t_data *data)
{
	t_redir	*current_redir;

	while (par_list->next)
		par_list = par_list->next;
	current_redir = par_list->redirection;
	data->fd_stdout = STDOUT_FILENO;
	if (!current_redir)
		return (0);
	while (current_redir->next)
		current_redir = current_redir->next;
	if (current_redir->type == 1)
	{
		if (!ft_strcmp(current_redir->token, ">"))
			data->fd_stdout = open(current_redir->name,
					O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (!ft_strcmp(current_redir->token, ">>"))
			data->fd_stdout = open(current_redir->name,
					O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (data->fd_stdout < 0)
			return (perror(current_redir->name), 1);
	}
	return (0);
}
