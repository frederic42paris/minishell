/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/24 21:13:52 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_envp(char **envp)
{
	int		i;
	int		count;
	char	**copy;

	count = 0;
	while (envp[count] != NULL)
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (copy == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (copy[i] == NULL)
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*tok_list;
	t_parse	*par_list;
	t_env	*env_list;
	t_data	*data;
	char	**environ;

	if (argc > 1 || argv[1] != NULL)
		exit_program("Minishell does not take arguments.");
	data = malloc(sizeof(t_data));
	data->exit_status = 0;
	tok_list = NULL;
	par_list = NULL;
	env_list = NULL;
	store_env_list(envp, &env_list);
	environ = copy_envp(envp);
	while (1)
	{
		data->exit_string = ft_itoa(data->exit_status);
		data->exit_len = ft_strlen(data->exit_string);
		disable_signal();
		if (take_input(data))
			continue ;
		if (check_input(data->input))
			continue ;
		store_path(environ, data);
		create_token_list(data, &tok_list, env_list);
		display_token_list(tok_list);

		count_nb_pipe(tok_list, data);
		get_num_token(tok_list, data);
		free(data->input);
		if (check_bracket_dup(tok_list) || check_bracket_error(tok_list, data))
		{
			free_token_list(&tok_list);
			continue ;
		}

		create_parse_list(tok_list, &par_list, environ);
		store_redirection(tok_list, &par_list);
		store_command(tok_list, par_list);
		free_token_list(&tok_list);
		check_infile(par_list->redirection);
		check_outfile(par_list->redirection);
		search_command(par_list, data);
		display_parse_list(par_list);
		enable_signal();
		if (par_list->builtin && data->has_pipe)
		{
			free_token_list(&tok_list);
			continue ;
		}
		if (data->has_pipe < 1)
			exec_single_cmd(par_list, &environ, data);
		else if (data->has_pipe >= 1)
			exec_multiple_cmd(par_list, environ, data);
		free(data->exit_string);
		free_parse_list(&par_list);
	}
	return (0);
}
