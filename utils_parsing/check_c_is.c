/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_c_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:43:03 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 18:08:45 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	is_space(char c)
{
	if (c == ' ' && c != '\0')
		return (1);
	else
		return (0);
}

int	is_single_quote(char c)
{
	if (c == 39 && c != '\0')
		return (1);
	else
		return (0);
}

int	is_quote(char c)
{
	if (c == 39 || c == '"')
		return (1);
	else
		return (0);
}

int	is_alnum(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}
