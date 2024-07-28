/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:52:05 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 18:47:43 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_operator(t_token *element, char *str)
{
	element->operator = malloc(element->len + 1);
	element->word = NULL;
	ft_strlcpy(element->operator, str, element->len + 1);
}

void	store_single_quote(t_token *element, char *str)
{
	element->i++;
	while (not_single_quote(str[element->i]))
		copy_word(element, str);
	if (str[element->i] != '\0')
		element->i++;
}

void	store_dbl_quote(t_token *element, char *str, t_env *env_l, t_data *data)
{
	element->i++;
	while (not_double_quote(str[element->i]))
	{
		if (str[element->i] == '$' && str[element->i + 1] == '?')
			copy_exit(element, data);
		else if (str[element->i] == '$' && is_alnum(str[element->i + 1]))
			expand_word(element, str, env_l);
		else
			copy_word(element, str);
	}
	if (str[element->i] != '\0')
		element->i++;
}

void	store_no_quote(t_token *element, char *str, t_env *env_l, t_data *data)
{
	while (not_meta_quote(str[element->i]))
	{
		if (str[element->i] == '$' && str[element->i + 1] == '?')
			copy_exit(element, data);
		else if (str[element->i] == '$' && is_quote(str[element->i + 1]))
			element->i++;
		else if (str[element->i] == '$' && is_alnum(str[element->i + 1]))
			expand_word(element, str, env_l);
		else
			copy_word(element, str);
	}
}

void	store_string(t_token *element, char *str, t_env *env_list, t_data *data)
{
	if (is_meta(str[0]))
		store_operator(element, str);
	else
	{
		element->word = malloc(element->len + 1);
		element->operator = NULL;
		while (not_meta(str[element->i]))
		{
			if (str[element->i] == 39)
				store_single_quote(element, str);
			else if (str[element->i] == '"')
				store_dbl_quote(element, str, env_list, data);
			else
				store_no_quote(element, str, env_list, data);
		}
		element->word[element->j] = '\0';
	}
}
