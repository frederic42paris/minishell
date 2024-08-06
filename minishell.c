/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/06 18:11:43 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, t_env *env_list)
{
	enable_signal();
	if (data->exit_string)
		free(data->exit_string);
	data->exit_string = ft_itoa(data->exit_status);
	data->exit_len = ft_strlen(data->exit_string);
	data->fd_stdin = STDIN_FILENO;
	data->fd_stdout = STDOUT_FILENO;
	if (data->exit_string == NULL)
	{
		printf("Malloc error\n");
		exit(EXIT_FAILURE);
	}
	data->env = env_list;
}

void	init_tok_list(t_token **tok_list, t_data *data, t_env *env_list)
{
	store_path(env_list, data);
	create_token_list(data, tok_list, env_list);
	count_nb_pipe(*tok_list, data);
	get_num_token(*tok_list, data);
	free(data->input);
}

void	start_exec(t_data *data, t_parse *par_list, t_env *env_list)
{
	t_parse	*current;

	current = par_list;
	data->num_cmd = count_cmds(par_list);
	if (data->environ)
		free_array(data->environ);
	data->environ = transform_envlist(env_list);
	if (data->has_pipe < 1)
		exec_single_cmd(par_list, data->environ, data, &env_list);
	else if (data->has_pipe >= 1)
		exec_multiple_cmd(par_list, data);
}

void	make_it_loop(t_data *data, t_env *env_list,
				t_token *tok_list, t_parse *par_list)
{
	while (1)
	{
		init_data(data, env_list);
		if (take_input(data, env_list) || check_input(data->input))
			continue ;
		init_tok_list(&tok_list, data, env_list);
		if (check_empty_redirection(tok_list))
		{
			free_token_list(&tok_list);
			continue ;
		}
		create_parse_list(tok_list, &par_list);
		store_redirection(tok_list, par_list);
		store_command(tok_list, par_list);
		free_token_list(&tok_list);
		search_command(par_list, data);
		if (open_infile(par_list, data) || open_outfile(par_list, data))
		{
			free_parse_list(&par_list);
			continue ;
		}
		start_exec(data, par_list, env_list);
		free_parse_list(&par_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*tok_list;
	t_parse	*par_list;
	t_data	*data;
	t_env	*env_list;

	if (argc > 1 || argv[1] != NULL)
		exit_program("Minishell does not take arguments.");
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	ft_memset(data, 0, sizeof(t_data));
	data->environ = NULL;
	tok_list = NULL;
	par_list = NULL;
	env_list = NULL;
	if (store_env_list(envp, &env_list) == 1)
		return (1);
	make_it_loop(data, env_list, tok_list, par_list);
	return (0);
}
