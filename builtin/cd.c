/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:01 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/06 17:44:51 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_input(t_parse *cmds)
{
	int	res;

	res = 0;
	while (cmds->cmd_array[res])
		res++;
	return (res);
}

int	func_cd(t_parse *cmds)
{
	char	*tmp;

	if (count_input(cmds) > 2)
		return (ft_putendl_fd("cd: too many arguments", STDERR_FILENO), 1);
	if (!cmds->cmd_array[1])
	{
		tmp = getenv("HOME");
		if (!tmp)
			return (ft_putendl_fd("cd: No such file or directory",
					STDERR_FILENO), 1);
		if (chdir(tmp) != 0)
			return (perror("cd"), 1);
	}
	else if (chdir(cmds->cmd_array[1]) != 0)
		return (perror("cd"), 1);
	return (0);
}
