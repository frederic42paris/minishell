/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:30:32 by rrichard          #+#    #+#             */
/*   Updated: 2024/08/06 16:26:03 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_multi_cmd(t_parse *cmds, t_data *data, int std_in, int std_out)
{
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	if (std_in != STDIN_FILENO)
		close(std_in);
	if (std_out != STDOUT_FILENO)
		close(std_out);
	if (execve(cmds->cmd_array[0], cmds->cmd_array, cmds->environ) == -1)
	{
		perror("execve");
		free_exit(cmds, data);
		if (errno == ENOENT)
			exit(127);
		else
			exit(1);
	}
}

void	execute_multi_builtin(t_parse *cmds, t_data *data, int std_in, int std_out)
{
	dup2(std_in, data->fd_stdin);
	dup2(std_out, data->fd_stdout);
	exec_builtin(cmds, data, &data->env);
	free_exit(cmds, data);
	exit(EXIT_SUCCESS);
}

void	exec_out(int (*fd)[2], pid_t *pid, t_parse *cmds, t_data *data)
{
	printf("dat num cmd = %d\n", data->num_cmd);
	pid[data->num_cmd - 1] = fork();
	if (pid[data->num_cmd - 1] == 0)
	{
		printf("CMDS IS : %s\n", cmds->cmd_array[0]);
		if (!is_builtin(cmds))
			execute_multi_cmd(cmds, data, fd[data->num_cmd - 1][0], fd[0][1]);
		else
		{
			dup2(fd[data->num_cmd - 1][0], data->fd_stdin);
			dup2(fd[0][1], data->fd_stdout);
			if (fd[data->num_cmd - 1][0] != STDIN_FILENO)
				close(fd[data->num_cmd - 1][0]);
			if (fd[0][1] != STDOUT_FILENO)
				close(fd[0][1]);
			exec_builtin(cmds, data, &data->env);
			free_exec(data->fd, data->pid, NULL);
			free_exit(cmds, data);
			exit(EXIT_SUCCESS);
		}
	}
	close(fd[data->num_cmd - 1][0]);
	wait_loop(pid, data);
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
			printf("CMDS IS : %s\n", cmds->cmd_array[0]);
			close_child(data, fd, i);
			if (i == 0)
			{
				if (!is_builtin(cmds))
					execute_multi_cmd(cmds, data, fd[0][0], fd[1][1]);
				else
				{
					dup2(fd[0][0], data->fd_stdin);
					dup2(fd[1][1], data->fd_stdout);
					if (fd[0][0] != STDIN_FILENO)
						close(fd[0][0]);
					if (fd[1][1] != STDOUT_FILENO)
						close(fd[1][1]);
					exec_builtin(cmds, data, &data->env);
					free_exec(data->fd, data->pid, NULL);
					free_exit(cmds, data);
					exit(EXIT_SUCCESS);
				}
			}
			else
			{
				if (!is_builtin(cmds))
					execute_multi_cmd(cmds, data, fd[i][0], fd[i + 1][1]);
				else
				{
					dup2(fd[i][0], data->fd_stdin);
					dup2(fd[i + 1][1], data->fd_stdout);
					if (fd[i][0] != STDIN_FILENO)
						close(fd[i][0]);
					if (fd[i + 1][1] != STDOUT_FILENO)
						close(fd[i + 1][1]);
					exec_builtin(cmds, data, &data->env);
					free_exec(data->fd, data->pid, NULL);
					free_exit(cmds, data);
					exit(EXIT_SUCCESS);
				}
			}
			exit(EXIT_SUCCESS);
		}
		if (i != 0)
			close(fd[i][0]);
		close(fd[i + 1][1]);
		cmds = cmds->next;
		i++;
	}
	exec_out(fd, pid, cmds, data);
	if (fd[0][0] != STDIN_FILENO)
		close(fd[0][0]);
}

void	exec_multiple_cmd(t_parse *cmds, t_data *data)
{
	int		(*fd)[2];
	pid_t	*pid;
	int		i;

	fd = malloc(sizeof(int [2]) * (data->has_pipe + 1));
	pid = malloc(sizeof(pid_t) * data->num_cmd);
	if (!pid || !fd)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	fd[0][0] = data->fd_stdin;
	fd[0][1] = data->fd_stdout;
	if (check_paths(cmds))
		return ;
	i = 1;
	while (i <= data->has_pipe)
	{
		if (pipe(fd[i]) == -1)
			free_exec(&fd, &pid, "pipe failed");
		i++;
	}
	data->pid = &pid;
	data->fd = &fd;
	exec_pipes(cmds, data, fd, pid);
	free_exec(&fd, &pid, NULL);
}
