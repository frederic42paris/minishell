/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:21 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/17 14:47:04 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "env";
	while (str[i] && echo[i])
	{
		if (str[i] == echo[i])
			i++;
		else
			return (0);
	}
	if (str[i] == '\0' && echo[i] == '\0')
		return (1);
	return (0);
}

void	func_env(t_parse *cmds, t_env **env)
{
	if (cmds->cmd_array[1])
		printf("env: ‘%s’: No such file or directory\n", cmds->cmd_array[1]);
	else
		display_env_list(*env);
}
