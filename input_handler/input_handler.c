/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:58:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/30 14:05:33 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	take_input(t_data *data)
{
	char	cwd[1024];
	char	*pretty_prompt;

	getcwd(cwd, sizeof(cwd));
	pretty_prompt = ft_strjoin(cwd, ">");
	if (!pretty_prompt)
		return (1);
	data->input = readline(pretty_prompt);
	free(pretty_prompt);
	if (data->input == NULL)
	{
		free_array(data->all_paths);
		free(data);
		exit(0);
	}
	if (ft_strlen(data->input) != 0)
	{
		add_history(data->input);
		return (0);
	}
	else
		return (1);
}
