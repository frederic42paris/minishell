/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:30 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/22 14:51:55 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_check_args(char *str)
{
	int	count_digits;

	count_digits = 0;
	if (ft_strtol(str, NULL, 10) > INT_MAX
		|| ft_strtol(str, NULL, 10) < INT_MIN)
		return (FALSE);
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		count_digits++;
		str++;
	}
	if (*str != '\0' || count_digits > 10)
		return (FALSE);
	return (TRUE);
}

void	normal_exit(t_parse *cmds_list, int exit_code)
{
	if (cmds_list->old_stdin != -1)
		close(cmds_list->old_stdout);
	if (cmds_list->old_stdout != -1)
		close(cmds_list->old_stdin);
	exit(exit_code);
}

void	func_exit(t_parse *cmds)
{
	int		num_args;

	num_args = 0;
	while (cmds->cmd_array[num_args])
		num_args++;
	if (cmds->cmd_array[1])
	{
		if (!ft_check_args(cmds->cmd_array[1]))
		{
			printf("exit: %s: numeric argument required\n", cmds->cmd_array[1]);
			normal_exit(cmds, 2);
		}
		else if (num_args > 2)
			return ((void)printf("exit: too many arguments\n"));
		else
		{
			printf("exit\n");
			normal_exit(cmds, ft_atoi(cmds->cmd_array[1]) % 256);
		}
	}
	else
	{
		printf("exit\n");
		normal_exit(cmds, 0);
	}
}
