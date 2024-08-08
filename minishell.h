/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:55 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/08 18:15:42 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

typedef struct s_token
{
	char			*word;
	char			*operator;
	char			**environ;
	int				num;
	int				index;
	int				j;
	int				i;
	int				len;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_env
{
	char			*env_var;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_data
{
	char			**all_paths;
	int				has_pipe;
	int				pos;
	char			*input;
	int				num_cmd;
	int				exit_status;
	int				num_token;
	int				exit_len;
	char			*exit_string;
	int				fd_stdin;
	int				fd_stdout;
	t_env			*env;
	int				(**fd)[2];
	pid_t			**pid;
	char			**environ;
}					t_data;

typedef struct s_redir
{
	int				type;
	char			*name;
	char			*token;
	int				exist;
	int				access;
	struct s_redir	*next;
	struct s_redir	*prev;
}					t_redir;

typedef struct s_parse
{
	char			**cmd_array;
	int				infile_nb;
	int				outfile_nb;
	t_redir			*redirection;
	char			*path;
	int				builtin;
	struct s_parse	*next;
	struct s_parse	*prev;
}					t_parse;

/////////////////////////////////////////////////////////////////////////

// error handler
void				exit_program(char *s);
char				*ft_shield_strdup(const char *str);

// input
int					take_input(t_data *data, t_env *env_list);
int					check_input(char const *str);
int					check_empty_redirection(t_token *tok_list);
int					check_empty_cmd(t_token *tok_list);

// execution
void				free_array(char **line);
void				free_fail(t_parse *cmds, t_data *data);
void				exec_multiple_cmd(t_parse *cmds, t_data *data);
void				exec_single_cmd(t_parse *cmds_list, char **environ,
						t_data *data, t_env **env_list);
t_bool				check_paths(t_parse *cmds);
int					count_cmds(t_parse *cmds);
void				free_exec(int (**fd)[2], pid_t **pid, char *str);
char				**transform_envlist(t_env *env_list);
int					listlen(t_env *env_list);
void				wait_loop(pid_t *pid, t_data *data);
void				end_exec(pid_t *pid, int (*fd)[2], t_parse *cmds,
						t_data *data);
void				exec_pipes(t_parse *cmds, t_data *data,
						int (*fd)[2], pid_t *pid);
void				exit_error(t_parse *cmds, t_data *data);

// built-in
int					is_builtin(t_parse *cmds);
int					exec_builtin(t_parse *cmds,
						t_data *data, t_env **env_list);
int					func_echo(t_parse *cmds, t_data *data);
int					func_pwd(t_parse *cmds, t_data *data);
int					func_cd(t_parse *cmds, t_data *data);
int					func_exit(t_parse *cmds, t_data *data);
int					func_env(t_parse *cmds, t_env *env_list, t_data *data);
int					func_export(t_parse *cmds, t_env **env_list, t_data *data);
int					func_unset(t_parse *cmds, t_env **env_list, t_data *data);
void				print_echo(t_parse *cmds, int i,
						int nextline_flag, t_data *data);
int					check_export_variable(char *s);
int					count_input(t_parse *cmds);
t_env				*find_env_var(char *name, t_env *env);
t_env				*sort_env(t_env *env_copy, t_env *current);
void				free_exit(t_parse *cmds, t_data *data);

//  lexical analysis
int					create_token_list(t_data *data, t_token **tok_list,
						t_env *env_list);
void				free_token_list(t_token **tok_list);
void				get_num_token(t_token *tok_list, t_data *data);
void				get_len_pos(t_data *data,
						t_env *env_list, t_token *element);
int					store_string(t_token *element, char *str,
						t_env *env_list, t_data *data);
void				copy_word(t_token *element, char *str);
void				expand_word(t_token *element, char *str, t_env *env_list);
char				*env_path(t_env *env_list, int len, char *string);
void				copy_exit(t_token *element, t_data *data);
void				display_token_list(t_token *tok_list);

//  parsing
int					create_parse_list(t_token *tok_list, t_parse **par_list);
void				display_parse_list(t_parse *par_list, t_data *data);
int					store_command(t_token *tok_list, t_parse *par_list);
int					search_command(t_parse *par_list, t_data *data);
int					store_redirection(t_token *tok_list, t_parse *par_list);
void				free_parse_list(t_parse **par_list);

// data
void				count_nb_pipe(t_token *tok_list, t_data *data);
void				free_data(t_data	*data);

// open fd
int					open_infile(t_parse *par_list, t_data *data);
int					open_outfile(t_parse *par_list, t_data *data);

//  env
int					store_env_list(char **envp, t_env **env_list);
int					store_path(t_env *env_list, t_data *data);
void				free_env_list(t_env **env_list);
int					push_env_list(t_env **env_list, const char *str);

// utils parsing
int					is_meta(char c);
int					is_bracket(char c);
int					count_words_pipe(t_token *tok_list);
int					not_meta_quote(char c);
int					not_meta(char c);
int					not_double_quote(char c);
int					not_single_quote(char c);
int					is_double_bracket(char c, char d);
int					is_space(char c);
int					is_quote(char c);
int					is_alnum(char c);

// gnl
char				*get_next_line(int fd);

// signals
void				disable_signal(void);
void				enable_signal(void);

#endif