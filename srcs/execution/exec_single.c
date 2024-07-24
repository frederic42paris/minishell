/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/24 17:26:58 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (std_in != STDIN_FILENO)
	{
		dup2(std_in, STDIN_FILENO);
		close(std_in);
	}
	if (std_out != STDOUT_FILENO)
	{
		dup2(std_out, STDOUT_FILENO);
		close(std_out);
	}
	if (execve(cmd.cmd_array[0], cmd.cmd_array, environ) == -1)
	{
		perror("execve");
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
		*std_out = open(cmds->redirection->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (EXIT_SUCCESS);
}

void	single_cmd(t_parse *cmds, char **environ, t_data *data)
{
	int		fd_in;
	int		fd_out;
	int		status;
	pid_t	fork_id;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	if (cmds->redirection)
	{
		if (prepare_file_descriptors(&fd_in, &fd_out, cmds))
			return ;
	}
	fork_id = fork();
	if (fork_id == 0)
		execute_cmd(*cmds, environ, fd_in, fd_out);
	waitpid(fork_id, &status, 0);
	data->exit_status = WEXITSTATUS(status);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
}

void	exec_single_cmd(t_parse *cmds_list, char ***environ, t_data *data)
{
	int		builtin_check;
	char	*tmp;

	if (!cmds_list->cmd_array[0])
		return ;
	builtin_check = is_builtin(cmds_list);
	if (builtin_check > 0)
		data->exit_status = exec_builtin(builtin_check, cmds_list, environ);
	else
	{
		if (cmds_list->path)
		{
			tmp = ft_strdup(cmds_list->path);
			free(cmds_list->cmd_array[0]);
			cmds_list->cmd_array[0] = tmp;
		}
		else
			return ((void)printf("minishell: command not found: %s\n", cmds_list->cmd_array[0]));
		single_cmd(cmds_list, *environ, data);
	}
}
