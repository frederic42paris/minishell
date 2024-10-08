NAME = minishell

#SRCS AND OBJS FOR COMPILING

SRCS = minishell.c error_handler/error_controler.c\
input_handler/input_handler.c\
builtin/echo.c\
builtin/pwd.c\
builtin/cd.c\
builtin/exit.c\
builtin/export.c\
builtin/unset.c\
builtin/env.c\
builtin/export_utils.c\
builtin/find_builtin.c\
input_error/check_empty_redirection.c\
input_error/check_input.c\
lexical_analysis/store_string_utils.c\
lexical_analysis/create_token_list.c\
lexical_analysis/display_token_list.c\
lexical_analysis/free_token_list.c\
lexical_analysis/get_len_pos.c\
lexical_analysis/store_string.c\
parsing/create_parse_list.c\
parsing/display_parse_list.c\
parsing/free_parse_list.c\
parsing/search_command.c\
parsing/store_command.c\
parsing/store_redirection.c\
signals/signals.c\
store_data/count_nb_pipe.c\
store_data/free_data.c\
store_data/get_num_token.c\
store_data/store_path.c\
store_env/free_env_list.c\
store_env/store_env_list.c\
store_env/env_utils.c\
utils_parsing/count_words.c\
utils_parsing/check_char.c\
utils_parsing/check_meta.c\
execution/exec_free.c \
execution/exec_multiple.c \
execution/exec_single.c \
execution/prepare_multipipe.c \
execution/prepare_execution.c \
open_infile.c \
open_outfile.c \
shield.c \

INCLUDES = libft/
OBJDIR = .obj

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

#FLAGS 
CC = cc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
CLIB = ./libft/libft.a
DEBUGGER = -g3

all : $(NAME)

$(NAME) : $(OBJS)
		make -C libft
		$(CC) $(OBJS) -I $(INCLUDES) -o $(NAME) $(CLIB) $(LDFLAGS) 

$(OBJDIR)/%.o : %.c
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) $(DEBUGGER) -c $< -o $@

clean :
		rm -rf $(OBJDIR)

fclean : clean
		rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re