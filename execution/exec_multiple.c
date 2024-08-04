/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:30:32 by rrichard          #+#    #+#             */
/*   Updated: 2024/08/04 13:16:34 by ftanon           ###   ########.fr       */
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

void	execute_cmd_multiple(t_parse *cmd, t_data *data, t_env *env, int i)
{
	dup2(data->fd[i][0], STDIN_FILENO);
	dup2(data->fd[i + 1][1], STDOUT_FILENO);
	if (data->fd[i][0] != STDIN_FILENO)
		close(data->fd[i][0]);
	if (data->fd[i + 1][1] != STDOUT_FILENO)
		close(data->fd[i + 1][1]);
	if (execve(cmd->cmd_array[0], cmd->cmd_array, cmd->environ) == -1)
	{
		printf("%s: command not found\n", cmd->cmd_array[0]);
		free_array(cmd->environ);
		free_data(data);
		free_parse_list(&cmd);
		free_env_list(&env);
		exit(EXIT_FAILURE);
	}
}

void	execute_cmd_last(t_parse *cmd, t_data *data, t_env *env, int i)
{
	dup2(data->fd[i][0], STDIN_FILENO);
	dup2(data->fd[0][1], STDOUT_FILENO);
	if (data->fd[i][0] != STDIN_FILENO)
		close(data->fd[i][0]);
	if (data->fd[0][1] != STDOUT_FILENO)
		close(data->fd[0][1]);
	if (execve(cmd->cmd_array[0], cmd->cmd_array, cmd->environ) == -1)
	{
		printf("%s: command not found\n", cmd->cmd_array[0]);
		free_array(cmd->environ);
		free_data(data);
		free_parse_list(&cmd);
		free_env_list(&env);
		exit(EXIT_FAILURE);
	}
}

void	exec_out(t_parse *cmds, t_data *data, t_env *env)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	data->pid[data->num_cmd - 1] = fork();
	if (data->pid[data->num_cmd - 1] == 0)
	{
		if (data->fd[0][0] != STDIN_FILENO)
			close(data->fd[0][0]);
		execute_cmd_last(cmds, data, env, data->num_cmd - 1);
		exit(EXIT_SUCCESS);
	}
	close(data->fd[data->num_cmd - 1][0]);
	i = 0;
	while (i < data->num_cmd)
	{
		waitpid(data->pid[i], &status, 0);
		if (i == data->num_cmd - 1)
			data->exit_status = WEXITSTATUS(status);
		i++;
	}
	if (data->fd[0][1] != STDOUT_FILENO)
		close(data->fd[0][1]);
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



void	exec_pipes(t_parse *cmds, t_data *data, t_env *env)
{
	int	i;

	i = 0;
	while (i < data->num_cmd - 1)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			close_child(data, data->fd, i);
			if (i == 0)
				execute_cmd_multiple(cmds, data, env, 0);
				// execute_cmd_multiple(cmds, data, fd[0][0], fd[1][1]);
			else
				execute_cmd_multiple(cmds, data, env, i);
				// execute_cmd_multiple(cmds, data, fd[i][0], fd[i + 1][1]);
			exit(EXIT_SUCCESS);
		}
		if (i != 0)
			close(data->fd[i][0]);
		close(data->fd[i + 1][1]);
		cmds = cmds->next;
		i++;
	}
	exec_out(cmds, data, env);
	if (data->fd[0][0] != STDIN_FILENO)
		close(data->fd[0][0]);
}

void	exec_multiple_cmd(t_parse *cmds, t_data *data, t_env *env)
{
	int		i;

	data->fd = malloc(sizeof(int [2]) * (data->has_pipe + 1));
	data->fd[0][0] = data->fd_stdin;
	data->fd[0][1] = data->fd_stdout;
	if (check_paths(cmds))
		return ;
	data->pid = malloc(sizeof(pid_t) * data->num_cmd);
	if (!data->pid)
	{
		free(data->fd);
		return ((void)printf("Malloc error\n"));
	}
	i = 1;
	while (i <= data->has_pipe)
	{
		if (pipe(data->fd[i]) == -1)
			free_exec(&data->fd, &data->pid, "pipe failed");
		i++;
	}
	exec_pipes(cmds, data, env);
	free_exec(&data->fd, &data->pid, NULL);
}
