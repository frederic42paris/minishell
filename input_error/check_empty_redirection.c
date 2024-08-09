/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:18:01 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/09 09:49:35 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_empty_redirection(t_token *tok_list)
{
	while (tok_list)
	{
		if (tok_list->operator && is_bracket(tok_list->operator[0]))
		{
			tok_list = tok_list->next;
			if (!tok_list
				|| (tok_list->operator && tok_list->operator[0] == '|'))
			{
				printf("Error : invalid command\n");
				return (1);
			}
		}
		if (tok_list)
			tok_list = tok_list->next;
	}
	return (0);
}

char	*init_ope_char(t_token *tok_list)
{
	char	*str;

	str = NULL;
	if (tok_list && tok_list->operator)
		str = tok_list->operator;
	return (str);
}

int	check_empty_cmd(t_token *tok_list)
{
	char	*str;

	str = init_ope_char(tok_list);
	if (tok_list)
		tok_list = tok_list->next;
	while (tok_list)
	{
		if (tok_list->operator)
		{
			if (str)
			{
				if (ft_strncmp(str, "|", 1) == 0
					&& ft_strncmp(tok_list->operator, "|", 1) == 0)
					return (ft_putendl_fd("Error: invalid command", 2), 1);
			}
			else
				str = tok_list->operator;
		}
		else
			str = NULL;
		if (tok_list)
			tok_list = tok_list->next;
	}
	return (0);
}

int	count_fd(t_redir *redir, int i)
{
	while (redir)
	{
		if (redir->type == i)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	check_infile(t_parse *par_list, t_data *data)
{
	if (data->has_pipe == 0)
		return (0);
	if (par_list && par_list->redirection && count_fd(par_list->redirection, 1))
		return (ft_putendl_fd("Error: invalid command", 2), 1);
	par_list = par_list->next;
	while (par_list->next)
	{
		if (par_list->redirection)
			return (ft_putendl_fd("Error: invalid command", 2), 1);
		par_list = par_list->next;
	}	
	if (data->has_pipe > 1)
		par_list = par_list->next;
	if (par_list && par_list->redirection && count_fd(par_list->redirection, 0))
		return (ft_putendl_fd("Error: invalid command", 2), 1);
	return (0);
}
