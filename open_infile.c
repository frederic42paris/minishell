/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:38:41 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/05 11:26:06 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "printf.h"

void	handle_heredoc(t_data *data, char *limiter)
{
	char	*line;
	int		fd[2];

	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter))
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		ft_putstr_fd(line, fd[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd[1]);
	data->fd_stdin = fd[0];
}

int	open_infile(t_parse *par_list, t_data *data)
{
	char	*last_infile;
	t_redir	*current;

	current = par_list->redirection;
	last_infile = NULL;
	while (current)
	{
		if (current->type == 0)
		{
			last_infile = current->name;
			if (!ft_strcmp(current->token, "<<"))
			{
				handle_heredoc(data, last_infile);
				return (0);
			}
		}
		current = current->next;
	}
	if (last_infile)
	{
		data->fd_stdin = open(last_infile, O_RDONLY);
		if (data->fd_stdin < 0)
			return (perror(last_infile), 1);
	}
	return (0);
}
