/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/03 16:48:50 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tok_list = NULL;
	par_list = NULL;
	env_list = NULL;
	if (store_env_list(envp, &env_list) == 1)
		return (1);
	while (1)
	{
		if (data->exit_string)
			free(data->exit_string);
		data->exit_string = ft_itoa(data->exit_status);
		// data->exit_string = ft_strdup("0");
		data->exit_len = ft_strlen(data->exit_string);
		if (data->exit_string == NULL)
			return (1);
		// printf("exit status : %d\n", data->exit_status);
		// disable_signal();
		// free(data->exit_string);

		if (take_input(data, env_list))
			continue ;
		if (check_input(data->input))
			continue ;
		if (store_path(env_list, data))
			return (1);
		if (create_token_list(data, &tok_list, env_list))
			return (1);
		// display_token_list(tok_list);
		count_nb_pipe(tok_list, data);
		get_num_token(tok_list, data);
		free(data->input);
		if (check_empty_redirection(tok_list))
		{
			free_token_list(&tok_list);
			continue ;
		}
		if (create_parse_list(tok_list, &par_list))
			return (1);
		if (store_redirection(tok_list, par_list))
			return (1);
		if (store_command(tok_list, par_list))
			return (1);
		free_token_list(&tok_list);
		check_infile(par_list->redirection);
		check_outfile(par_list->redirection);
		if (search_command(par_list, data))
			return (1);
		if (open_infile(par_list, data))
			return (1);
		if (open_outfile(par_list, data))
			return (1);
		display_parse_list(par_list);

		enable_signal();
		data->num_cmd = count_cmds(par_list);
		par_list->environ = transform_envlist(env_list);
		if (data->has_pipe < 1)
			exec_single_cmd(par_list, par_list->environ, data, &env_list);
		else if (data->has_pipe >= 1)
			exec_multiple_cmd(par_list, data);
		free_array(par_list->environ);
		// free_env_list(&env_list);
		
		// printf("chiffre %d\n", data->exit_len);
		// printf("string %s\n", data->exit_string);
		free_parse_list(&par_list);
	}
	return (0);
}
