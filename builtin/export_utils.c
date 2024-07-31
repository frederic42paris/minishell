/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:49:28 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/31 15:42:02 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspecial(int c)
{
	if (c == ';' || c == '&' || c == '|' || c == '>'
		|| c == '<' || c == '(' || c == ')'
		|| c == '{' || c == '}' || c == '$' || c == '*'
		|| c == '?' || c == '[' || c == ']' || c == '#'
		|| c == '\\' || c == '!' || c == '~' || c == ' '
		|| c == '\"' || c == '\'' || c == '`')
		return (1);
	return (0);
}

t_bool	check_export_variable(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isalpha(s[i]) || s[i] == '_')
			i++;
		else if (ft_isdigit(s[i]) && i != 0)
			i++;
		else if (s[i] == '\\')
		{
			if (ft_isspecial(s[i + 1]) || (ft_isdigit(s[i + 1] && i == 0)))
				return (printf("export: `%s': not a valid identifier\n", s), FALSE);
			i++;
		}
		else
			return (printf("export: `%s': not a valid identifier\n", s), FALSE);
	}
	return (TRUE);
}

// t_env	*sort_env(t_env *env_copy, t_env *current)
// {
// 	int		swapped;
// 	char	*tmp;

// 	swapped = 1;
// 	while (swapped)
// 	{
// 		swapped = 0;
// 		current = env_copy;
// 		while (current && current->next != NULL)
// 		{
// 			if (ft_strncmp(current->env_var, current->next->env_var, 1) > 0)
// 			{
// 				tmp = current->env_var;
// 				current->env_var = current->next->env_var;
// 				current->next->env_var = tmp;
// 				swapped = 1;
// 			}
// 			current = current->next;
// 		}
// 	}
// 	current = env_copy;
// 	return (current);
// }
