/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/23 15:52:25 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_child_pipe(t_parse *cmds_list, t_pipe *pipe_info, char **env_copy,
// 		int i)
// {
// 	if (parse_path(cmds_list->cmd_array, cmds_list->path))
// 	{
// 		redirection(cmds_list, pipe_info, i);
// 		execve(cmds_list->path, cmds_list->cmd_array, env_copy);
// 		exit(0);
// 	}
// 	else
// 		exit(127);
// }

// t_pipe	*init_pipeinfo(t_parse *cmds_list)
// {
// 	t_pipe	*pipe_info;

// 	pipe_info = malloc(sizeof(t_pipe));
// 	if (pipe_info == NULL)
// 		pipe_null_check();
// 	pipe_info->total_cmds = count_cmds(cmds_list);
// 	return (pipe_info);
// }

// void	close_extra_files(t_parse *cmds_list)
// {
// 	if (cmds_list->next != NULL)
// 		close(cmds_list->pipe_fdo);
// 	if (cmds_list->prev != NULL)
// 	{
// 		close(cmds_list->prev->pipe_fdi);
// 	}
// }

// void	close_files(t_parse *cmds_list)
// {
// 	if (cmds_list->infile_name)
// 		close(cmds_list->infile);
// 	if (cmds_list->outfile_access)
// 		close(cmds_list->outfile);
// }

// void	runtime_shell(t_parse *cmds_list, char **env_copy, t_data *data,
// 		t_env **env_list)
// {
// 	t_pipe	*pipe_info;
// 	pid_t	fork_id;
// 	int		i;
// 	t_parse	*head;

// 	head = cmds_list;
// 	i = 0;
// 	pipe_info = init_pipeinfo(cmds_list);
// 	init_pid_array(pipe_info);
// 	while (i < pipe_info->total_cmds)
// 	{
// 		pipe_init(pipe_info, cmds_list, i, data);
// 		fork_id = fork();
// 		if (fork_id == 0)
// 		{
// 			if (getfile(cmds_list))
// 			{
// 				if (is_builtin(cmds_list) > 0)
// 				{
// 					redirection(cmds_list, pipe_info, i);
// 					exec_builtin(is_builtin(cmds_list), cmds_list, env_list);
// 				}
// 				else
// 					init_child_pipe(cmds_list, pipe_info, env_copy, i);
// 				exit(0);
// 			}
// 			else
// 				close_no_file(cmds_list);
// 		}
// 		store_pid(pipe_info, fork_id);
// 		close_extra_files(cmds_list);
// 		i++;
// 		cmds_list = cmds_list->next;
// 	}
// 	close_parent(head, pipe_info, data);
// }
