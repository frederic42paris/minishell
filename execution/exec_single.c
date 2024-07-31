/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/31 17:35:22 by rrichard         ###   ########.fr       */
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

void	execute_cmd(t_parse cmd, char **environ, int std_in, int std_out)
{
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	if (std_in != STDIN_FILENO)
		close(std_in);
	if (std_out != STDOUT_FILENO)
		close(std_out);
	if (execve(cmd.cmd_array[0], cmd.cmd_array, environ) == -1)
	{
		printf("%s: command not found\n", cmd.cmd_array[0]);
		exit(EXIT_FAILURE);
	}
}

t_bool	prepare_file_descriptors(int *std_in, int *std_out, t_parse *cmds)
{
	int	i;
	int	tmp;

	i = 0;
	while (i < cmds->infile_nb - 1)
	{
		tmp = open(cmds->redirection->name, O_RDONLY);
		if (tmp < 0)
			return (perror(cmds->redirection->name), EXIT_FAILURE);
		close(tmp);
		i++;
		cmds->redirection = cmds->redirection->next;
	}
	if (!cmds->redirection->type)
	{
		*std_in = open(cmds->redirection->name, O_RDONLY);
		if (*std_in < 0)
			return (perror(cmds->redirection->name), EXIT_FAILURE);
		cmds->redirection = cmds->redirection->next;
	}
	if (cmds->redirection)
		*std_out = open(cmds->redirection->name,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (EXIT_SUCCESS);
}

void	single_cmd(t_parse *cmds, char **environ, t_data *data)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	if (cmds->redirection)
	{
		if (prepare_file_descriptors(&fd[0], &fd[1], cmds))
			return ;
	}
	pid = fork();
	if (pid == 0)
		execute_cmd(*cmds, environ, fd[0], fd[1]);
	waitpid(pid, &status, 0);
	data->exit_status = WEXITSTATUS(status);
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
}

void	exec_single_cmd(t_parse *cmds_list, char **environ, t_data *data, t_env **env_list)
{
	int		builtin_check;
	char	*tmp;

	if (!cmds_list->cmd_array[0])
		return ;
	builtin_check = is_builtin(cmds_list);
	if (builtin_check > 0)
		data->exit_status
			= exec_builtin(builtin_check, cmds_list, data, env_list);
	else
	{
		if (cmds_list->path)
		{
			tmp = ft_strdup(cmds_list->path);
			free(cmds_list->cmd_array[0]);
			cmds_list->cmd_array[0] = tmp;
		}
		single_cmd(cmds_list, environ, data);
	}
}
