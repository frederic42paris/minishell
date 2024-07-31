/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:57:00 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/30 18:38:50 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len_src(char *str)
{
	int	i;

	i = 0;
	while (is_alnum(str[i]))
	{
		i++;
	}
	return (i);
}

char	*env_path(t_env *env_list, int len, char *string)
{
	int	env_len;

	while (env_list)
	{
		env_len = 0;
		while (env_list->env_var[env_len] != '=')
			env_len++;
		if (env_len == len && ft_strncmp(env_list->env_var, string, len) == 0)
			return (env_list->env_var + len + 1);
		else
			env_list = env_list->next;
	}
	return (NULL);
}

void	expand_word(t_token *element, char *str, t_env *env_list)
{
	int		src_len;
	int		k;
	char	*dst;

	element->i++;
	src_len = get_len_src(str + element->i);
	dst = env_path(env_list, src_len, str + element->i);
	if (dst == NULL)
		element->word[element->j] = '\0';
	else
	{
		k = 0;
		while (dst[k])
		{
			element->word[element->j] = dst[k];
			k++;
			element->j++;
		}
	}
	element->i = element->i + src_len;
}

void	copy_exit(t_token *element, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->exit_len)
	{
		element->word[element->j] = data->exit_string[i];
		i++;
		element->j++;
	}
	element->i = element->i + 2;
}

void	copy_word(t_token *element, char *str)
{
	element->word[element->j] = str[element->i];
	element->i++;
	element->j++;
}
