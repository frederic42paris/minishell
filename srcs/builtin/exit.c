/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:30 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/31 14:13:41 by rrichard         ###   ########.fr       */
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

int	func_exit(t_parse *cmds)
{
	if (cmds->cmd_array[1])
	{
		if (!ft_check_args(cmds->cmd_array[1]))
		{
			printf("exit\nexit: %s: numeric argument required\n", cmds->cmd_array[1]);
			exit(2);
		}
		else if (count_input(cmds) <= 2)
		{
			printf("exit\n");
			exit(ft_atoi(cmds->cmd_array[1]) % 256);
		}
	}
	else
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	return ((void)printf("exit: too many arguments\n"), EXIT_FAILURE);
}
