/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/23 18:01:22 by rrichard         ###   ########.fr       */
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

void	get_last_infile(t_parse *cmds)
{
	while (cmds->)
}

int	exec_cmd(t_parse *cmds, char **environ, t_data *data)
{
	int		fd_in;
	int		fd_out;
	int		status;
	pid_t	fork_id;

	if (cmds->redirection->type)
	{
		fd_in = open(cmds->redirection->name, O_RDONLY);
		if (cmds->redirection)
	}
	fork_id = fork();
	if (fork_id == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2()
	}
}

void	exec_shell(t_parse *cmds_list, char ***environ, t_data *data)
{
	int		builtin_check;
	pid_t	fork_id;
	int		status;
	int		result;

	status = 0;
	builtin_check = is_builtin(cmds_list);
	if (builtin_check > 0)
		data->exit_status = exec_builtin(builtin_check, cmds_list, environ);
	else
	{
		cmds_list->redirection->type
		fork_id = fork();
		if (fork_id == 0)
		{
			
			free_parse_list(&cmds_list);
			free_array(data->all_paths);
			free_env_list(env_list);
			free(data);
			if (result == 1)
				exit(127);
			else
				exit(0);
		}
		waitpid(fork_id, &status, 0);
		// printf("loop %d\n", WEXITSTATUS(status));
		data->exit_status = WEXITSTATUS(status);
	}
}
