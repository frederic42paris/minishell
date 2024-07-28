/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:06:16 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 15:08:14 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		printf("infile_nb : %d\n", par_list->infile_nb);
		printf("outfile_nb : %d\n", par_list->outfile_nb);
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
