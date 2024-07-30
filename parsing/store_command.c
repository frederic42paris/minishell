/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:01:57 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/30 17:29:34 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_meta(t_token *tok_list)
{
	int	len;

	len = 0;
	while (tok_list)
	{
		if (tok_list->operator && tok_list->operator[0] == '|')
			break ;
		if (tok_list->operator && (tok_list->operator[0] == '>'
				|| tok_list->operator[0] == '<'))
		{
			tok_list = tok_list->next;
			tok_list = tok_list->next;
			continue ;
		}
		len++;
		tok_list = tok_list->next;
	}
	return (len);
}

int	split_command(t_token *tok_list, t_parse *par_list)
{
	int	i;
	int	j;

	j = 0;
	i = count_words_meta(tok_list);
	free_array(par_list->cmd_array);
	par_list->cmd_array = (char **)malloc(sizeof(char *) * (i + 1));
	if (par_list->cmd_array == NULL)
		return (1);
	while (tok_list)
	{
		if (tok_list->operator && tok_list->operator[0] == '|')
			break ;
		if (tok_list->operator && is_bracket(tok_list->operator[0]))
		{
			tok_list = tok_list->next;
			tok_list = tok_list->next;
			continue ;
		}
		par_list->cmd_array[j] = ft_strdup(tok_list->word);
		if (par_list->cmd_array[j] == NULL)
			return (1);
		j++;
		tok_list = tok_list->next;
	}
	par_list->cmd_array[j] = NULL;
	return (0);
}

int	store_command(t_token *tok_list, t_parse *par_list)
{
	int	i;
	int	k;

	while (par_list)
	{
		i = 0;
		k = 0;
		i = count_words_pipe(tok_list);
		if (split_command(tok_list, par_list))
			return (1);
		while (k < i)
		{
			tok_list = tok_list->next;
			k++;
		}
		if (tok_list && tok_list->operator && tok_list->operator[0] == '|')
			tok_list = tok_list->next;
		par_list = par_list->next;
	}
	return (0);
}
