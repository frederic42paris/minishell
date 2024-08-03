/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:30:32 by rrichard          #+#    #+#             */
/*   Updated: 2024/08/03 16:08:25 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_check_redirection(t_parse *cmds, int ncmds)
{
	int	result;
	int	n;

	n = 1;
	result = 0;
	while (cmds)
	{
		if (cmds->redirection)
		{
			if (n == 1 && cmds->redirection->type == 0)
				result |= 1;
			else if (n == ncmds && cmds->redirection->type == 1)
				result |= 2;
		}
		n++;
		cmds = cmds->next;
	}
	return (result);
}

void	exec_out(int (*fd)[2], pid_t *pid, t_parse cmds, t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	pid[data->num_cmd - 1] = fork();
	if (pid[data->num_cmd - 1] == 0)
	{
		if (fd[0][0] != STDIN_FILENO)
			close(fd[0][0]);
		execute_cmd(cmds, cmds.environ, fd[data->num_cmd - 1][0], fd[0][1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[data->num_cmd - 1][0]);
	i = 0;
	while (i < data->num_cmd)
	{
		waitpid(pid[i], &status, 0);
		if (i == data->num_cmd - 1)
			data->exit_status = WEXITSTATUS(status);
		i++;
	}
	if (fd[0][1] != STDOUT_FILENO)
		close(fd[0][1]);
}

void	close_child(t_data *data, int (*fd)[2], int i)
{
	int	j;

	close(fd[i + 1][0]);
	close(fd[i][1]);
	if (fd[0][1] != STDOUT_FILENO)
		close(fd[0][1]);
	j = i + 2;
	while (j < data->has_pipe + 1)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	if (i != 0)
	{
		if (fd[0][0] != STDIN_FILENO)
			close(fd[0][0]);
	}
}

void	exec_pipes(t_parse *cmds, t_data *data, int (*fd)[2], pid_t *pid)
{
	int	i;

	i = 0;
	while (i < data->num_cmd - 1)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			close_child(data, fd, i);
			if (i == 0)
				execute_cmd(*cmds, cmds->environ, fd[0][0], fd[1][1]);
			else
				execute_cmd(*cmds, cmds->environ, fd[i][0], fd[i + 1][1]);
			exit(EXIT_SUCCESS);
		}
		if (i != 0)
			close(fd[i][0]);
		close(fd[i + 1][1]);
		cmds = cmds->next;
		i++;
	}
	exec_out(fd, pid, *cmds, data);
	if (fd[0][0] != STDIN_FILENO)
		close(fd[0][0]);
}

void	exec_multiple_cmd(t_parse *cmds, t_data *data)
{
	int		(*fd)[2];
	pid_t	*pid;
	int		i;

	fd = malloc(sizeof(int [2]) * (data->has_pipe + 1));
	fd[0][0] = data->fd_stdin;
	fd[0][1] = data->fd_stdout;
	if (check_paths(cmds))
		return ;
	pid = malloc(sizeof(pid_t) * data->num_cmd);
	if (!pid)
	{
		free(fd);
		return ((void)printf("Malloc error\n"));
	}
	i = 1;
	while (i <= data->has_pipe)
	{
		if (pipe(fd[i]) == -1)
			free_exec(&fd, &pid, "pipe failed");
		i++;
	}
	exec_pipes(cmds, data, fd, pid);
	free_exec(&fd, &pid, NULL);
}
