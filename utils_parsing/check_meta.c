/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:43:22 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/30 13:59:35 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_meta_quote(char c)
{
	if (c != ' ' && c != '\0' && c != '"' && c != 39 && c != '|' && c != '>'
		&& c != '<')
		return (1);
	else
		return (0);
}

int	not_meta(char c)
{
	if (c != ' ' && c != '\0' && c != '|' && c != '>' && c != '<')
		return (1);
	else
		return (0);
}

int	is_meta(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	else
		return (0);
}

int	is_bracket(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	is_double_bracket(char c, char d)
{
	if (c == '>' && d == '>')
		return (1);
	else if (c == '<' && d == '<')
		return (1);
	else
		return (0);
}
