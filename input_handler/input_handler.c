/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/31 16:12:26 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	take_input(t_data *data)
{
	char	*cwd;
	char	*pretty_prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	pretty_prompt = ft_strjoin(cwd, ">");
	free(cwd);
	if (!pretty_prompt)
		return (1);
	data->input = readline(pretty_prompt);
	free(pretty_prompt);
	if (data->input == NULL)
	{
		free_data(data);
		free_env_list(&env_list);
		exit(0);
	}
	if (ft_strlen(data->input) != 0)
	{
		add_history(data->input);
		return (0);
	}
	return (1);
}
