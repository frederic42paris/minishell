/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:30:32 by rrichard          #+#    #+#             */
/*   Updated: 2024/07/26 16:09:27 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_check_redirection(t_parse *cmds, int ncmds)
{
	int	n;
	int	infile;
	int	outfile;

	n = 1;
	infile = 0;
	outfile = 0;
	while (cmds)
	{
		if (cmds->redirection)
		{
			if (n == 1 && cmds->redirection->type == 0)
				infile = 1;
			else if (n == ncmds && cmds->redirection->type == 1)
				outfile = 1;
		}
		n++;
		cmds = cmds->next;
	}
	if (infile == 1 && outfile == 1)
		return (3);
	else if (infile == 0 && outfile == 1)
		return (2);
	else if (infile == 1 && outfile == 0)
		return (1);
	return (0);
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
}

void	exec_multiple_cmd(t_parse *cmds, t_data *data, char **environ)
{
	int		(*fd)[2];
	pid_t	*pid;
	int		i;

	(void)environ;
	data->num_cmd = count_cmds(cmds);
	fd = malloc(sizeof(int [2]) * (data->has_pipe + 1));
	prepare_in_out(cmds, data, &fd);
	if (fd[0][0] < 0 || fd[0][1] < 0 || check_paths(cmds))
		return ;
	pid = malloc(sizeof(pid_t) * data->num_cmd);
	i = 1;
	while (i <= data->has_pipe)
	{
		if (pipe(fd[i]) == -1)
		{
			free(pid);
			free(fd);
			perror("pipe failed");
			return ;
		}
		i++;
	}
	exec_pipes(cmds, data, fd, pid);
	if (fd[0][0] != STDIN_FILENO)
		close(fd[0][0]);
	if (fd[0][1] != STDOUT_FILENO)
		close(fd[0][1]);
}
