/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:09:42 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/23 17:17:27 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_pwd(char *str)
// {
// 	char	*echo;
// 	int		i;

// 	i = 0;
// 	echo = "pwd";
// 	while (str[i] && echo[i])
// 	{
// 		if (str[i] == echo[i])
// 			i++;
// 		else
// 			return (0);
// 	}
// 	if (str[i] == '\0' && echo[i] == '\0')
// 		return (1);
// 	return (0);
// }

int	func_pwd(t_parse *cmds)
{
	char	cwd[1024];
	int		count_cmds;

	count_cmds = count_arr_length(cmds->cmd_array);
	if (count_cmds < 2)
	{
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
		return (0);
	}
	else
		return (printf("pwd: too many arguments\n"), 1);
}
