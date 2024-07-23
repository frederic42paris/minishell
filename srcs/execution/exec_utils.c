/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/23 18:35:51 by rrichard         ###   ########.fr       */
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

// int	parse_path(char **cmds, char *path)
// {
// 	if (!path || access(path, X_OK | F_OK) != 0)
// 	{
// 		printf("%s: Command not found\n", cmds[0]);
// 		return (0);
// 	}
// 	else
// 	{
// 		return (1);
// 	}
// }

// int	init_child(t_parse *cmds_list, char **env_copy)
// {
// 	if (getfile(cmds_list))
// 	{
// 		only_redirection(cmds_list);
// 		if (parse_path(cmds_list->cmd_array, cmds_list->path))
// 		{
// 			execve(cmds_list->path, cmds_list->cmd_array, env_copy);
// 			return (0);
// 		}
// 		else
// 			return (1);
// 	}
// 	return (0);
// }

// void	exec_shell_builtin(t_parse *cmds_list, int builtin_check,
// 		t_env **env_list)
// {
// 	if (getfile(cmds_list))
// 	{
// 		only_redirection(cmds_list);
// 		exec_builtin(builtin_check, cmds_list, env_list);
// 	}
// }

// void	get_last_infile(t_parse *cmds)
// {
// 	t_redir	*current;
// 	int		count_in;
// 	int		count_out;

// 	current = cmds->redirection;
// 	while (current->exist)
// 	{
// 		if (current->type)
// 			count_out++;
// 		else
// 			count_in++;
// 		if (current->)
// 		current = current->next;
// 	}
// }

void	exec_cmd(t_parse *cmds, char **environ, t_data *data)
{
	int		fd_in;
	int		fd_out;
	int		status;
	pid_t	fork_id;

	if (cmds->redirection->type)
	{
		if (!cmds->redirection->type)
		{
			fd_in = open(cmds->redirection->name, O_RDONLY);
			cmds->redirection = cmds->redirection->next;
		}
		else if (cmds->redirection->type)
			fd_out = open(cmds->redirection->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	fork_id = fork();
	if (fork_id == 0)
	{
		if (fd_in)
			dup2(fd_in, STDIN_FILENO);
		else if (fd_out)
			dup2(fd_out, STDOUT_FILENO);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		if (execve(cmds->path, cmds->cmd_array, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		waitpid(fork_id, &status, 0);
		data->exit_status = WEXITSTATUS(status);
	}
}

void	exec_shell(t_parse *cmds_list, char ***environ, t_data *data)
{
	int		builtin_check;

	builtin_check = is_builtin(cmds_list);
	if (builtin_check > 0)
		data->exit_status = exec_builtin(builtin_check, cmds_list, environ);
	else
	{
		exec_cmd(cmds_list, *environ, data);
	}
}
