/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/27 22:16:29 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
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

int	is_bracket_pipe(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	not_operator_dollar(char c)
{
	if (c != ' ' && c != '\0' && c != '"' && c != 39 && c != '|' && c != '>'
		&& c != '<' && c != '$')
		return (1);
	else
		return (0);
}

int	not_operator(char c)
{
	if (c != ' ' && c != '\0' && c != '"' && c != 39 && c != '|' && c != '>'
		&& c != '<')
		return (1);
	else
		return (0);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '"')
		return (1);
	else
		return (0);
}

int	not_space_pipe(char c)
{
	if (c != ' ' && c != '\0' && c != '|')
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

char	*env_path(int len, char *string, t_token *element)
{
	int	env_len;
	int	i;
	char	*env_var;

	i = 0;
	while (element->environ[i])
	{
		env_len = 0;
		env_var = element->environ[i];
		while (env_var[env_len] != '=' && env_var[env_len] != '\0')
			env_len++;
		if (env_len == len && ft_strncmp(env_var, string, len) == 0)
			return (env_var + len + 1);
		i++;
	}
	return (NULL);
}

void	expand_len_pos(t_data *data, t_token *element)
{
	int		i;
	int		len;
	char	*string;
	char	*result;

	data->pos++;
	i = data->pos;
	len = 0;
	while (not_operator_dollar(data->input[i]))
	{
		i++;
		len++;
	}
	string = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(string, data->input + data->pos, len + 1);
	result = env_path(len, string, element);
	data->pos = i;
	if (result != NULL)
		element->len = element->len + ft_strlen(result);
	free(string);
}

void	len_single_quote(t_data *data, t_token *element)
{
	data->pos++;
	while (not_single_quote(data->input[data->pos]))
	{
		element->len++;
		data->pos++;
	}
	if (data->input[data->pos] != '\0')
		data->pos++;
}

void	len_double_quote(t_data *data, t_token *element)
{
	data->pos++;
	while (not_double_quote(data->input[data->pos]))
	{
		if (data->input[data->pos] == '$' && data->input[data->pos] == '?')
		{
			element->len = element->len + data->exit_len;
			data->pos = data->pos + data->exit_len;
		}
		else if (data->input[data->pos] == '$' && data->input[data->pos + 1] == '"')
		{
			element->len = element->len + 1;
			data->pos = data->pos + 1;
		}
		else if (data->input[data->pos] == '$')
		{
			expand_len_pos(data, element);
		}
		else
		{
			element->len++;
			data->pos++;
		}
	}
	if (data->input[data->pos] != '\0')
		data->pos++;
}

void	len_no_quote(t_data *data, t_token *element)
{
	while (not_operator(data->input[data->pos]))
	{
		if (data->input[data->pos] == '$' && data->input[data->pos] == '?')
		{
			element->len = element->len + data->exit_len;
			data->pos = data->pos + data->exit_len;
		}
		else if (data->input[data->pos] == '$' && is_single_quote(data->input[data->pos + 1]))
			data->pos = data->pos + 1;
		else if (data->input[data->pos] == '$' && is_separator(data->input[data->pos + 1]))
		{
			element->len = element->len + 1;
			data->pos = data->pos + 1;
		}
		else if (data->input[data->pos] == '$')
			expand_len_pos(data, element);
		else
		{
			element->len++;
			data->pos++;
		}
	}
}

void	get_len_pos(t_data *data, t_token *element)
{
	if (is_double_bracket(data->input[data->pos], data->input[data->pos + 1]))
	{
		element->len = 2;
		data->pos = data->pos + 2;
	}
	else if (is_bracket_pipe(data->input[data->pos]))
	{
		element->len = 1;
		data->pos = data->pos + 1;
	}
	else
	{
		while (not_space_pipe(data->input[data->pos]))
		{
			if (data->input[data->pos] == 39)
				len_single_quote(data, element);
			else if (data->input[data->pos] == '"')
				len_double_quote(data, element);
			else
				len_no_quote(data, element);
		}
	}
}

void	store_operator(t_token *element, char *str)
{
	element->operator= malloc(element->len + 1);
	element->word = NULL;
	ft_strlcpy(element->operator, str, element->len + 1);
}

int	get_len_src(char *str)
{
	int	i;

	i = 0;
	while (not_operator_dollar(str[i]))
	{
		i++;
	}
	return (i);
}

void	copy_word(t_token *element, char *str)
{
	element->word[element->j] = str[element->i];
	element->i++;
	element->j++;
}

void	expand_word(t_token *element, char *str)
{
	int		src_len;
	int		k;
	char	*src;
	char	*dst;

	element->i++;
	src_len = get_len_src(str + element->i);
	src = malloc(sizeof(char) * (src_len + 1));
	ft_strlcpy(src, str + element->i, src_len + 1);
	dst = env_path(src_len, str + element->i, element);
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
	free(src);
	element->i = element->i + src_len;
}

void	copy_exit(t_token *element,  t_data *data)
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

void	store_single_quote(t_token *element, char *str)
{
	element->i++;
	while (not_single_quote(str[element->i]))
		copy_word(element, str);
	if (str[element->i] != '\0')
		element->i++;
}

void	store_double_quote(t_token *element, char *str, t_data *data)
{
	element->i++;
	while (not_double_quote(str[element->i]))
	{
		if (str[element->i] == '$' && str[element->i + 1] == '?')
			copy_exit(element, data);
		else if (str[element->i] == '$' && str[element->i + 1] == '"')
			copy_word(element, str);
		else if (str[element->i] == '$')
			expand_word(element, str);
		else
			copy_word(element, str);
	}
	if (str[element->i] != '\0')
		element->i++;
}

void	store_no_quote(t_token *element, char *str, t_data *data)
{
	while (not_operator(str[element->i]))
	{
		if (str[element->i] == '$' && str[element->i + 1] == '?')
			copy_exit(element, data);
		else if (str[element->i] == '$' && is_single_quote(str[element->i + 1]))
			element->i++;
		else if (str[element->i] == '$' && is_separator(str[element->i + 1]))
			copy_word(element, str);
		else if (str[element->i] == '$')
			expand_word(element, str);
		else
			copy_word(element, str);
	}
}

void	store_string(t_token *element, char *str, t_data *data)
{
	if (is_operator(str[0]))
		store_operator(element, str);
	else
	{
		element->word = malloc(element->len + 1);
		element->operator = NULL;
		while (not_space_pipe(str[element->i]))
		{
			if (str[element->i] == 39)
				store_single_quote(element, str);
			else if (str[element->i] == '"')
				store_double_quote(element, str, data);
			else
				store_no_quote(element, str, data);
		}
		element->word[element->j] = '\0';
	}
}

void	push_token_list(t_token **tok_list, char *str, t_data *data, char **environ)
{
	t_token	*element;
	t_token	*last;

	last = *tok_list;
	element = malloc(sizeof(t_token));
	element->environ = environ;
	element->len = 0;
	element->j = 0;
	element->i = 0;
	get_len_pos(data, element);
	store_string(element, str, data);
	element->next = NULL;
	if (*tok_list == NULL)
	{
		*tok_list = element;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
}

// **** attention segfault
// tok_list = NULL;
void	create_token_list(t_data *data, t_token **tok_list, char **environ)
{
	data->pos = 0;
	data->num_token = 0;
	while (data->input[data->pos] != '\0')
	{
		while (is_space(data->input[data->pos]))
			data->pos++;
		if (data->input[data->pos] == '\0')
			break ;
		push_token_list(tok_list, data->input + data->pos, data, environ);
	}
}

void	display_token_list(t_token *tok_list)
{
	// tok_list->num = 0;
	printf("--------------------\n");
	while (tok_list)
	{
		if (tok_list->word)
			printf("[%s]\n", tok_list->word);
		if (tok_list->operator)
			printf("%s\n", tok_list->operator);
		tok_list = tok_list->next;
	}
	printf("--------------------\n");
}

void	get_num_token(t_token *tok_list, t_data *data)
{
	int	i;

	i = 0;
	while (tok_list)
	{
		i++;
		tok_list = tok_list->next;
	}
	data->num_token = i;
}

int	check_bracket_error(t_token *tok_list, t_data *data)
{
	int i;

	i = 0;
	if (data->num_token == 1 && tok_list->operator)
	{
		while (tok_list->operator[i])
			i++;
		if (i == 1 && is_operator(tok_list->operator[0]))
		{
			printf("Error : Invalid cmd\n");
			return (1);
		}
		else if (i == 2 && is_double_bracket(tok_list->operator[0],
				tok_list->operator[1]))
		{
			printf("Error : Invalid cmd\n");
			return (1);
		}
	}
	return (0);
}
