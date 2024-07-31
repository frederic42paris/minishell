/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:06:26 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/27 21:34:16 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_parse *cmds, int i, int nextline_flag)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (cmds->redirection)
	{
		if (!ft_strcmp(">>", cmds->redirection->token))
			fd = open(cmds->redirection->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (!ft_strcmp(">", cmds->redirection->token))
			fd = open(cmds->redirection->name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	}
	while (cmds->cmd_array[i])
	{
		ft_putstr_fd(cmds->cmd_array[i], fd);
		i++;
		if (cmds->cmd_array[i])
			ft_putstr_fd(" ", fd);
	}
	if (!nextline_flag)
		ft_putstr_fd("\n", fd);
	if (fd > 0 && fd != STDOUT_FILENO)
		close(fd);
}

int	func_echo(t_parse *cmds)
{
	int	nextline_flag;
	int	i;
	int	j;

	nextline_flag = 0;
	i = 1;
	while (cmds->cmd_array[i] && cmds->cmd_array[i][0] == '-')
	{
		j = 1;
		while (cmds->cmd_array[i][j] == 'n')
			j++;
		if (cmds->cmd_array[i][j] == '\0')
		{
			nextline_flag = 1;
			i++;
		}
		else
			break ;
	}
	print_echo(cmds, i, nextline_flag);
	return (0);
}
