/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:55 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/03 11:28:20 by rrichard         ###   ########.fr       */
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

typedef struct s_pipe
{
	pid_t			*pids;
	char			*limiter;
	int				total_cmds;
	int				only_redirect;
	int				tmp_file;
	int				num_cmd;
	int				counter;
}					t_pipe;

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
	int				only_cmd;
	int				num_redirections;
	int				pipe_fdi;
	int				pipe_fdo;
	int				infile;
	int				outfile;
	int				is_heredoc;
	int				tmp_file;
	char			*delimiter;
	int				fd_stdin;
	int				fd_stdout;
	struct s_parse	*next;
	struct s_parse	*prev;
	char			**environ;
}					t_parse;

/////////////////////////////////////////////////////////////////////////

// error handler
void				exit_program(char *s);
void				create_prompt(char **env);

// minishell
int					take_input(t_data *data, t_env *env_list);
void				print_dir(void);
int					process_string(char *str, char **parsed, char **parsedpipe);
void				exec_args(char **parsed);
void				exec_args_piped(char **parsed, char **parsedpipe);
int					own_cmd_handler(char **parsed);
int					count_arr_length(char **argv);
void				execution(t_parse *cmds_list, char **env_copy,
						t_pipe *pipe_info);
void				execute_pipeline(t_parse *cmds_list, char **env_copy,
						t_data *data);
int					count_cmds(t_parse *cmds_list);

// execution
void				free_array(char **line);
void				exec_multiple_cmd(t_parse *cmds, t_data *data);
void				exec_single_cmd(t_parse *cmds_list, char **environ, t_data *data, t_env **env_list);
void				execute_cmd(t_parse cmd, char **environ, int std_in, int std_out);
t_bool				prepare_file_descriptors(int *std_in, int *std_out, t_parse *cmds);
t_bool				check_paths(t_parse *cmds);
int					count_cmds(t_parse *cmds);
void				prepare_in_out(t_parse *cmds, t_data *data, int (**fd)[2]);
int					exec_check_redirection(t_parse *cmds, int ncmds);
void				free_exec(int (**fd)[2], pid_t **pid, char *str);
char				**transform_envlist(t_env *env_list);
int					listlen(t_env *env_list);

// built-in
int					is_builtin(t_parse *cmds);
int					exec_builtin(int func, t_parse *cmds, t_data *data, t_env **env_list);
int					func_echo(t_parse *cmds);
int					func_pwd(t_parse *cmds, t_data *data);
int					func_cd(t_parse *cmds);
int					func_exit(t_parse *cmds);
int					func_env(t_parse *cmds, t_env *env_list);
int					func_export(t_parse *cmds, t_env **env_list);
int					func_unset(t_parse *cmds, t_env **env_list);
void				print_echo(t_parse *cmds, int i, int nextline_flag);
int					check_export_variable(char *s);
int					count_input(t_parse *cmds);
t_env				*find_env_var(char *name, t_env *env);

//  lexical analysis
int					check_input(char const *str);
int					create_token_list(t_data *data, t_token **tok_list,
						t_env *env_list);
void				free_token_list(t_token **tok_list);
void				get_num_token(t_token *tok_list, t_data *data);
int					check_bracket_error(t_token *tok_list, t_data *data);
int					check_bracket_dup(t_token *tok_list);
int					check_empty_redirection(t_token *tok_list);
void				free_redirection(t_token	**tok_list);
void				get_len_pos(t_data *data, t_env *env_list, t_token *element);
int					store_string(t_token *element, char *str, t_env *env_list, t_data *data);
void				copy_word(t_token *element, char *str);
void				expand_word(t_token *element, char *str, t_env *env_list);
char				*env_path(t_env *env_list, int len, char *string);
void				copy_exit(t_token *element, t_data *data);

//  parsing
int					create_parse_list(t_token *tok_list, t_parse **par_list);
void				free_parse_list(t_parse **par_list);
void				display_parse_list(t_parse *par_list);
int					store_command(t_token *tok_list, t_parse *par_list);
void				check_outfile(t_redir *par_list);
void				check_infile(t_redir *par_list);
int					search_command(t_parse *par_list, t_data *data);
void				count_nb_pipe(t_token *tok_list, t_data *data);
int					store_redirection(t_token *tok_list, t_parse *par_list);
void				display_parse_list(t_parse *par_list);

// open fd
int					open_infile(t_parse *par_list);
int					open_outfile(t_parse *par_list);

//  env
int					store_env_list(char **envp, t_env **env_list);
int					store_path(t_env *env_list, t_data *data);
// void				delete_one_env(t_env **env_list, char *variable);
void				replace_one_env(t_env **env_list, char *env_val,
						char *variable, char *value);
void				free_env_list(t_env **env_list);
int					push_env_list(t_env **env_list, const char *str);

// data

void				free_data(t_data	*data);

// display
void				display_array(char **array);
void				display_token_list(t_token *tok_list);

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
int					is_single_quote(char c);
int					is_quote(char c);
int					is_alnum(char c);

// gnl
char				*get_next_line(int fd);

// signals

void				disable_signal(void);
void				enable_signal(void);

//	exit status

void				init_pid_array(t_pipe *pipe_info);
void				store_pid(t_pipe *pipe_info, pid_t fork_id);

// utils
size_t				ft_strlen(const char *string);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

// redirection
int					receive_input(char *input_name);
int					getfile(t_parse *cmds_list);
void				redirection(t_parse *cmds_list, t_pipe *pipe_info, int i);
void				pipe_init(t_pipe *pipe_info, t_parse *cmds_list, int i,
						t_data *data);
void				only_redirection(t_parse *cmds_list);
void				wait_pipe_files(t_pipe *pipe_info, t_data *data);
void				close_pipe_files(t_parse *cmds_list);
void				heredoc_check(t_parse *cmds_list);
void				middle_cmd(t_parse *cmds_list);
void				last_cmd(t_parse *cmds_list);
void				first_cmd(t_parse *cmds_list);
void				only_redirection(t_parse *cmds_list);
void				heredoc_check(t_parse *cmds_list);

void				close_no_file(t_parse *cmds_list);
void				close_pipe_files(t_parse *cmds_list);
void				init_child_pipe(t_parse *cmds_list, t_pipe *pipe_info,
						char **env_copy, int i);

void				push_num_cmd(int status, t_data *data);
void				open_heredoc(t_parse *cmds_list);
void				init_heredoc(t_parse *cmds_list);
void				pipe_null_check(void);
void				pipe_null_check(void);
void				close_no_file(t_parse *cmds_list);
void				close_parent(t_parse *head, t_pipe *pipe_info,
							t_data *data);
void				call_heredoc(t_parse *cmds_list);

#endif