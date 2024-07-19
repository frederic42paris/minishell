/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:30 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/19 22:47:04 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_alpha(char *s, t_parse *cmds_list)
{
	printf("exit: %s: numeric argument required\n", s);
	if (cmds_list->old_stdin != -1)
		close(cmds_list->old_stdout);
	if (cmds_list->old_stdout != -1)
		close(cmds_list->old_stdin);
	exit(1);
}

// void	control_many_args(t_parse *cmds_list)
// {
// 	printf("exit : too many arugments\n");
// 	if (cmds_list->old_stdin != -1)
// 		close(cmds_list->old_stdout);
// 	if (cmds_list->old_stdout != -1)
// 		close(cmds_list->old_stdin);
// 	exit(1);
// }

void	normal_exit(t_parse *cmds_list, int exit_code)
{
	printf("exit\n");
	if (cmds_list->old_stdin != -1)
		close(cmds_list->old_stdout);
	if (cmds_list->old_stdout != -1)
		close(cmds_list->old_stdin);
	exit(exit_code);
}

void	func_exit(t_parse *cmds)
{
	char	*endptr;
	long	exit_code;

	if (!cmds->cmd_array[1])
		normal_exit(cmds, EXIT_SUCCESS);
	if (cmds->cmd_array[1] && cmds->cmd_array[2])
		return ((void)printf("exit: too many arguments\n"));
	exit_code = ft_strtol(cmds->cmd_array[1], &endptr, 10);
	if (errno == ERANGE && (exit_code == LONG_MAX || exit_code == LONG_MIN))
		printf("exit: %s: numeric argument required\n", cmds->cmd_array[1]);
	else if (errno != 0 && exit_code == 0)
		printf("exit: %s: numeric argument required\n", cmds->cmd_array[1]);
	else if (endptr == cmds->cmd_array[1])
		printf("exit: %s: numeric argument required\n", cmds->cmd_array[1]);
	else if (*endptr != '\0')
		printf("exit: %s: numeric argument required\n", cmds->cmd_array[1]);
	else
		normal_exit(cmds, (int)(exit_code % 256));
}
