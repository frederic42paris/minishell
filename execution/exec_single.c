/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/06 15:30:52 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void	execute_cmd(t_parse *cmd, t_data *data, int fd[2], t_env *env)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
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

void	single_cmd(t_parse *cmds, t_data *data, t_env *env)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	fd[0] = data->fd_stdin;
	fd[1] = data->fd_stdout;
	pid = fork();
	if (pid == 0)
		execute_cmd(cmds, data, fd, env);
	waitpid(pid, &status, 0);
	data->exit_status = WEXITSTATUS(status);
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
}

void	exec_single_cmd(t_parse *cmds, char **envp, t_data *data, t_env **env)
{
	int		builtin_check;
	char	*tmp;

	(void)envp;
	if (!cmds->cmd_array[0])
	{
		if (data->fd_stdin != 0)
			close(data->fd_stdin);
		if (data->fd_stdin != 1)
			close(data->fd_stdout);
		return ;
	}
	builtin_check = is_builtin(cmds);
	if (builtin_check > 0)
		data->exit_status
			= exec_builtin(builtin_check, cmds, data, env);
	else
	{
		if (cmds->path)
		{
			tmp = ft_shield_strdup(cmds->path);
			free(cmds->cmd_array[0]);
			cmds->cmd_array[0] = tmp;
		}
		single_cmd(cmds, data, *env);
	}
}
