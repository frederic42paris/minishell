/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:52:05 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/05 11:25:57 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	store_operator(t_token *element, char *str)
{
	element->word = NULL;
	element->operator = malloc(element->len + 1);
	if (element->operator == NULL)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(element->operator, str, element->len + 1);
	return (0);
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

int	store_string(t_token *element, char *str, t_env *env_list, t_data *data)
{
	if (is_meta(str[0]))
	{
		if (store_operator(element, str))
			return (1);
		return (0);
	}
	element->operator = NULL;
	element->word = malloc(element->len + 1);
	if (element->word == NULL)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
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
	return (0);
}
