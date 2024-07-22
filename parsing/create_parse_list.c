/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parse_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:43:11 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/22 17:30:02 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_pipe_create(t_token *tok_list)
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

void	push_parse_list(t_parse **par_list, int i)
{
	t_parse	*element;
	t_parse	*last;

	last = *par_list;
	element = malloc(sizeof(t_parse));
	element->index = i;
	// element->infile_name = NULL;
	// element->infile_token = NULL;
	// element->infile_exist = 0;
	// element->infile_access = 0;
	// element->outfile_name = NULL;
	// element->outfile_token = NULL;
	// element->outfile_exist = 0;
	// element->outfile_access = 0;
	element->path = NULL;
	element->builtin = 0;
	element->next = NULL;
	element->old_stdin = -1;
	element->old_stdout = -1;
	element->cmd_array = (char **)ft_calloc(2, sizeof(char *));
	element->cmd_array[0] = (char *)ft_calloc (1, sizeof(char));
	if (*par_list == NULL)
	{
		*par_list = element;
		element->prev = NULL;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
}

void	create_parse_list(t_token *tok_list, t_parse **par_list)
{
	int	i;
	int	k;
	int	index;

	index = 0;
	while (tok_list)
	{
		index++;
		i = 0;
		k = 0;
		i = count_words_pipe_create(tok_list);
		push_parse_list(par_list, index);
		while (k < i)
		{
			tok_list = tok_list->next;
			k++;
		}
		if (tok_list && tok_list->operator && tok_list->operator[0] == '|')
			tok_list = tok_list->next;
	}
}

void	display_parser_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("[%s]", array[i]);
		i++;
	}
	if (i == 0)
		printf("%s", array[i]);
}

void	display_redir_list(t_redir *redir_list)
{
	if (redir_list)
	{
		printf("\n");
		printf("Redirection List : \n");
	}
	while (redir_list)
	{
		printf("file type : %d\n", redir_list->type);
		printf("file token : %s\n", redir_list->token);
		printf("file name : %s\n", redir_list->name);
		printf("file exist : %d\n", redir_list->exist);
		printf("file access : %d\n", redir_list->access);
		printf("\n");
		redir_list = redir_list->next;
	}
}

void	display_parse_list(t_parse *par_list)
{
	int	i;

	i = 0;
	printf("--------------------\n");
	while (par_list)
	{
		printf("\n");
		printf("Command %d\n", i);
		display_redir_list(par_list->redirection);
		printf("command_array : ");
		display_parser_array(par_list->cmd_array);
		printf("\n");
		printf("builtin : %d\n", par_list->builtin);
		printf("path : %s\n", par_list->path);
		par_list = par_list->next;
		i++;
	}
	printf("--------------------\n");
}

int	string_is_bracket(char *str)
{
	int	len;
	int	is_bracket;

	is_bracket = 0;
	len = ft_strlen(str);
	if (str[0] == '>' || str[0] == '<')
		is_bracket = 1;
	if (is_bracket == 1 && len == 1)
		return (1);
	return (0);
}

int	check_bracket_dup(t_token *tok_list)
{
	int		i;
	int		k;
	char	*string1;
	char	*string2;

	while (tok_list)
	{
		i = 0;
		k = 0;
		i = count_words_pipe_create(tok_list);
		string1 = tok_list->operator;
		while (k < i - 1)
		{
			tok_list = tok_list->next;
			k++;
		}
		string2 = tok_list->operator;
		tok_list = tok_list->next;
		if (string2 && string1)
		{
			if (string_is_bracket(string1) && string_is_bracket(string2))
			{
				printf("Error : invalid cmd\n");
				return (1);
			}
		}
		if (tok_list && tok_list->operator && tok_list->operator[0] == '|')
			tok_list = tok_list->next;
	}
	return (0);
}