/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:30:32 by rrichard          #+#    #+#             */
/*   Updated: 2024/08/08 18:14:19 by rrichard         ###   ########.fr       */
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
	data->fd_stdin = STDIN_FILENO;
	data->fd_stdout = STDOUT_FILENO;
	if (is_builtin(cmds))
		exec_builtin(cmds, data, &data->env);
	else if (execve(cmds->cmd_array[0], cmds->cmd_array, data->environ) == -1)
		exit_error(cmds, data);
}

void	exec_out(int (*fd)[2], pid_t *pid, t_parse *cmds, t_data *data)
{
	pid[data->num_cmd - 1] = fork();
	if (pid[data->num_cmd - 1] == 0)
	{
		execute_multi_cmd(cmds, data, fd[data->num_cmd - 1][0], fd[0][1]);
		free_exec(data->fd, data->pid, NULL);
		free_fail(cmds, data);
		exit(EXIT_SUCCESS);
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
	while (j < data->num_cmd)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
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
			execute_multi_cmd(cmds, data, fd[i][0], fd[i + 1][1]);
			free_exec(data->fd, data->pid, NULL);
			free_fail(cmds, data);
			exit(EXIT_SUCCESS);
		}
		if (fd[i][0] != STDIN_FILENO)
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
	{
		ft_putendl_fd("Error: invalid command", STDERR_FILENO);
		if (data->fd_stdin != STDIN_FILENO)
			close(data->fd_stdin);
		if (data->fd_stdout != STDOUT_FILENO)
			close(data->fd_stdout);
		free_exec(&fd, &pid, NULL);
		return ;
	}
	end_exec(pid, fd, cmds, data);
}
