/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:30:32 by rrichard          #+#    #+#             */
/*   Updated: 2024/07/25 22:02:13 by rrichard         ###   ########.fr       */
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

int	count_cmds(t_parse *cmds)
{
	int	res;

	res = 0;
	while (cmds)
	{
		if (cmds->path)
			res++;
		cmds = cmds->next;
	}
	return (res);
}

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

int	*prepare_in_out(t_parse *cmds, t_data *data)
{
	int	check;
	int	i;
	int	*stdin_out;

	i = 0;
	stdin_out = malloc(sizeof(int) * 2);
	check = exec_check_redirection(cmds, data->num_cmd);
	if (check == 3)
	{
		stdin_out[0] = open(cmds->redirection->name, O_RDONLY);
		while (i < data->num_cmd - 1)
		{
			i++;
			cmds = cmds->next;
		}
		stdin_out[1] = open(cmds->redirection->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		return (stdin_out);
	}
	else if (check == 2)
	{
		stdin_out[0] = STDIN_FILENO;
		while (i < data->num_cmd - 1)
		{
			i++;
			cmds = cmds->next;
		}
		stdin_out[1] = open(cmds->redirection->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		return (stdin_out);
	}
	else if (check == 1)
	{
		stdin_out[0] = open(cmds->redirection->name, O_RDONLY);
		stdin_out[1] = STDOUT_FILENO;
		return (stdin_out);
	}
	else
	{
		stdin_out[0] = STDIN_FILENO;
		stdin_out[1] = STDOUT_FILENO;
		return (stdin_out);
	}
}

void	exec_out(int *fd, int *stdin_out, pid_t pid, t_parse cmds)
{
	pid = fork();
	if (pid == 0)
	{
		execute_cmd(cmds, cmds.environ, fd[0], stdin_out[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
}

void	exec_multiple_cmd(t_parse *cmds, char **environ, t_data *data)
{
	int		(*fd)[2];
	int		i;
	int		status;
	pid_t	*pid;
	int		*stdin_out;

	data->num_cmd = count_cmds(cmds);
	stdin_out = prepare_in_out(cmds, data);
	if (stdin_out[0] < 0 || stdin_out[1] < 0)
		return (perror("open"));
	pid = malloc(sizeof(pid_t) * data->num_cmd);
	fd = malloc(sizeof(int *) * data->has_pipe);
	i = 0;
	status = 0;
	if (!check_paths(cmds))
	{
		while (i < data->has_pipe)
		{
			if (pipe(fd[i]) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			i++;
		}
		i = 0;
		while (i < data->num_cmd - 1)
		{
			pid[i] = fork();
			if (pid[i] == 0)
			{
				close(fd[i][0]);
				if (i == 0)
					execute_cmd(*cmds, environ, stdin_out[0], fd[i][1]);
				else
					execute_cmd(*cmds, environ, fd[i - 1][0], fd[i][1]);
				exit(EXIT_SUCCESS);
			}
			if (i != 0)
				close(fd[i - 1][0]);
			close(fd[i][1]);
			cmds = cmds->next;
			i++;
		}
		exec_out(fd[i - 1], stdin_out, pid[i], *cmds);
		i = 0;
		while (i < data->num_cmd)
		{
			waitpid(pid[i], &status, 0);
			if (i == data->num_cmd - 1)
				data->exit_status = WEXITSTATUS(status);
			i++;
		}
		if (stdin_out[0] != STDIN_FILENO)
			close(stdin_out[0]);
		if (stdin_out[1] != STDOUT_FILENO)
			close(stdin_out[1]);
	}
// 	// free pid and fds
}
