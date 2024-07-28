/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_c_isnot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:43:22 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 15:46:32 by ftanon           ###   ########.fr       */
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

int	not_double_quote(char c)
{
	if (c != '"' && c != '\0')
		return (1);
	else
		return (0);
}

int	not_single_quote(char c)
{
	if (c != 39 && c != '\0')
		return (1);
	else
		return (0);
}
