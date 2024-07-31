/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:49:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/31 11:21:35 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_len_pos(t_data *data, t_env *env_list, t_token *element)
{
	int		i;
	int		len;
	char	*result;

	data->pos++;
	i = data->pos;
	len = 0;
	while (is_alnum(data->input[i]))
	{
		i++;
		len++;
	}
	result = env_path(env_list, len, data->input + data->pos);
	if (result != NULL)
		element->len = element->len + ft_strlen(result);
	data->pos = i;
}

void	len_single_quote(t_data *data, t_token *element)
{
	data->pos++;
	while (not_single_quote(data->input[data->pos]))
	{
		element->len++;
		data->pos++;
	}
	if (data->input[data->pos] != '\0')
		data->pos++;
}

void	len_double_quote(t_data *data, t_env *env_list, t_token *element)
{
	data->pos++;
	while (not_double_quote(data->input[data->pos]))
	{
		if (data->input[data->pos] == '$' && data->input[data->pos + 1] == '?')
		{
			element->len = element->len + data->exit_len;
			data->pos = data->pos + data->exit_len;
		}
		else if (data->input[data->pos] == '$'
			&& is_alnum(data->input[data->pos + 1]))
			expand_len_pos(data, env_list, element);
		else
		{
			element->len++;
			data->pos++;
		}
	}
	if (data->input[data->pos] != '\0')
		data->pos++;
}

void	len_no_quote(t_data *data, t_env *env_list, t_token *element)
{
	while (not_meta_quote(data->input[data->pos]))
	{
		if (data->input[data->pos] == '$' && data->input[data->pos + 1] == '?')
		{
			element->len = element->len + data->exit_len;
			data->pos = data->pos + data->exit_len;
		}
		else if (data->input[data->pos] == '$'
			&& is_quote(data->input[data->pos + 1]))
			data->pos = data->pos + 1;
		else if (data->input[data->pos] == '$'
			&& is_alnum(data->input[data->pos + 1]))
			expand_len_pos(data, env_list, element);
		else
		{
			element->len++;
			data->pos++;
		}
	}
}

void	get_len_pos(t_data *data, t_env *env_list, t_token *element)
{
	if (is_double_bracket(data->input[data->pos], data->input[data->pos + 1]))
	{
		element->len = 2;
		data->pos = data->pos + 2;
	}
	else if (is_meta(data->input[data->pos]))
	{
		element->len = 1;
		data->pos = data->pos + 1;
	}
	else
	{
		while (not_meta(data->input[data->pos]))
		{
			if (data->input[data->pos] == 39)
				len_single_quote(data, element);
			else if (data->input[data->pos] == '"')
				len_double_quote(data, env_list, element);
			else
				len_no_quote(data, env_list, element);
		}
	}
}
