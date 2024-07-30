/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:49:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/30 17:08:51 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_len_pos(t_data *data, t_env *env_list, t_token *element)
{
	int		i;
	int		len;
	char	*string;
	char	*result;

	data->pos++;
	i = data->pos;
	len = 0;
	while (is_alnum(data->input[i]))
	{
		i++;
		len++;
	}
	string = malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (1);
	ft_strlcpy(string, data->input + data->pos, len + 1);
	result = env_path(env_list, len, string);
	data->pos = i;
	if (result != NULL)
		element->len = element->len + ft_strlen(result);
	free(string);
	return (0);
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

int	len_double_quote(t_data *data, t_env *env_list, t_token *element)
{
	int	i;

	i = 0;
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
			i = expand_len_pos(data, env_list, element);
		else
		{
			element->len++;
			data->pos++;
		}
		if (i == 1)
			return (1);
	}
	if (data->input[data->pos] != '\0')
		data->pos++;
	return (0);
}

int	len_no_quote(t_data *data, t_env *env_list, t_token *element)
{
	int	i;

	i = 0;
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
			i = expand_len_pos(data, env_list, element);
		else
		{
			element->len++;
			data->pos++;
		}
		if (i == 1)
			return (1);
	}
	return (0);
}

int	get_len_pos(t_data *data, t_env *env_list, t_token *element)
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
			else if (data->input[data->pos] == '"'
				&& len_double_quote(data, env_list, element))
				return (1);
			else
				if (len_no_quote(data, env_list, element))
					return (1);
		}
	}
	return (0);
}
