/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:30:32 by rrichard          #+#    #+#             */
/*   Updated: 2024/07/24 21:48:42 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_paths(t_parse *cmds)
{
	while (cmds)
	{
		if (!cmds->path)
			return ((void)printf("minishell: command not found: %s\n", cmds->cmd_array[0]), EXIT_FAILURE);
		free(cmds->cmd_array[0]);
		cmds->cmd_array[0] = ft_strdup(cmds->path);
 		cmds = cmds->next;
	}
	return (EXIT_SUCCESS);
}

void	exec_multiple_cmd(t_parse *cmds, char **environ, t_data *data)
{
	int		num_cmds = data->has_pipe + 1;
	int		num_pipes = data->has_pipe;
	int		fd[num_pipes][2];
	int		i = 0;
	pid_t	pid;
	pid_t	pid_out;
	int		status;
	int		fd_in, fd_out;

	status = 0;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	printf("num_cmds = %d\n", num_cmds);
	if (cmds->redirection)
	{
		if (prepare_file_descriptors(&fd_in, &fd_out, cmds))
			return ;
	}
	if (!check_paths(cmds))
	{
		while (i < num_pipes)
		{
			if (pipe(fd[i]) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			i++;
		}
		i = 0;
		while (i < num_cmds)
		{
			printf("CMD IS : %s\n", cmds->cmd_array[0]);
			pid = fork();
			if (pid == 0)
			{
				close(fd[i][0]);
				if (i == 0)
					execute_cmd(*cmds, environ, fd_in, fd[i][1]);
				else
					execute_cmd(*cmds, environ, fd[i - 1][0], fd[i][1]);
			}
			if (i != 0)
				close(fd[i - 1][0]);
			close(fd[i][1]);
			waitpid(pid, NULL, 0);
			cmds = cmds->next;
			i++;
		}
		pid_out = fork();
		if (pid == 0)
		{
			execute_cmd(*cmds, environ, fd[i - 1][0], fd_out);
		}
		close(fd[i - 1][0]);
		waitpid(pid_out, &status, 0);
		WEXITSTATUS(status);
	}
}
