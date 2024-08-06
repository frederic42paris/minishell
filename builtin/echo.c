/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:06:26 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/06 17:44:24 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_parse *cmds, int i, int nextline_flag, t_data *data)
{
	int	fd;

	fd = data->fd_stdout;
	while (cmds->cmd_array[i])
	{
		ft_putstr_fd(cmds->cmd_array[i], fd);
		i++;
		if (cmds->cmd_array[i])
			ft_putstr_fd(" ", fd);
	}
	if (!nextline_flag)
		ft_putstr_fd("\n", fd);
}

int	func_echo(t_parse *cmds, t_data *data)
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
	print_echo(cmds, i, nextline_flag, data);
	if (data->fd_stdin != STDIN_FILENO)
			close(data->fd_stdin);
	if (data->fd_stdout != STDOUT_FILENO)
		close(data->fd_stdout);
	return (0);
}
