/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:01:57 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/22 17:01:51 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_operator(t_token *tok_list)
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

int	count_words_pipe_search(t_token *tok_list)
{
	int	len;

	len = 0;
	while (tok_list)
	{
		if (tok_list->operator && tok_list->operator[0] == '|')
			break ;
		len++;
		tok_list = tok_list->next;
	}
	return (len);
}

void	split_command(t_token *tok_list, t_parse *par_list)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	j = 0;
	i = count_words_operator(tok_list);
	free_array(par_list->cmd_array);
	par_list->cmd_array = (char **)malloc(sizeof(char *) * (i + 1));
	while (tok_list)
	{
		if (tok_list->operator && tok_list->operator[0] == '|')
			break ;
		i = 0;
		if (tok_list->operator && (tok_list->operator[0] == '>'
				|| tok_list->operator[0] == '<'))
		{
			tok_list = tok_list->next;
			tok_list = tok_list->next;
			continue ;
		}
		while (tok_list)
		{
			if (tok_list->operator && (tok_list->operator[0] == '|'
					|| tok_list->operator[0] == '>'
					|| tok_list->operator[0] == '<'))
				break ;
			len = ft_strlen(tok_list->word);
			par_list->cmd_array[j] = (char *)malloc(sizeof(char) * (len
						+ 1));
			ft_strlcpy(par_list->cmd_array[j], tok_list->word, len + 1);
			j++;
			tok_list = tok_list->next;
		}
	}
	par_list->cmd_array[j] = NULL;
}

void	store_command(t_token *tok_list, t_parse *par_list)
{
	int	i;
	int	k;

	while (par_list)
	{
		i = 0;
		k = 0;
		i = count_words_pipe_search(tok_list);
		split_command(tok_list, par_list);
		while (k < i)
		{
			tok_list = tok_list->next;
			k++;
		}
		if (tok_list && tok_list->operator && tok_list->operator[0] == '|')
			tok_list = tok_list->next;
		par_list = par_list->next;
	}
}
