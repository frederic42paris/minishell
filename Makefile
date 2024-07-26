################################################################################
#                                   VARIABLES                                  #
################################################################################

NAME = minishell

CC = cc

CFLAGS = -Werror -Wall -Wextra -g

CSANIT = -g -fsanitize=address

# Directories
LIB_PATH = libft
INC_PATH = includes
SRCS_PATH = srcs
BONUS_PATH = bonus
OBJS_PATH = .obj/
LIBFT_SRC_PATH = $(LIB_PATH)/srcs
LIBFT_INC_PATH = $(LIB_PATH)/includes

# Library
LIBFT = $(LIB_PATH)/libft.a

# Source files and obj files
SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_FILES))
OBJS = $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)%.o)

# Include directories
INCS = -I$(INC_PATH) -I$(LIBFT_INC_PATH)

################################################################################
#                                   LIB_FILES                                  #
################################################################################

LIB_FILES =		libft.a

################################################################################
#                                   INC_FILES                                  #
################################################################################

INC_FILES =		minishell.h \

################################################################################
#                                   SRCS_FILES                                 #
################################################################################

SRCS_FILES =	minishell.c \
				builtin/cd.c \
				builtin/echo.c \
				builtin/env.c \
				builtin/exit.c \
				builtin/export.c \
				builtin/export_utils.c \
				builtin/find_builtin.c \
				builtin/pwd.c \
				builtin/unset.c \
				error_handler/error_controler.c \
				execution/exec_single.c \
				execution/exec_multiple.c \
				execution/prepare_multipipe.c \
				input_handler/input_handler.c \
				lexical_analysis/check_input.c \
				lexical_analysis/count_nb_pipe.c \
				lexical_analysis/create_token_list.c \
				lexical_analysis/free_token_list.c \
				parsing/check_infile.c \
				parsing/check_outfile.c \
				parsing/create_parse_list.c \
				parsing/free_parse_list.c \
				parsing/search_command.c \
				parsing/store_command.c \
				parsing/store_redirection.c \
				signals/signals.c \
				store_env/env_utils.c \
				store_env/free_env_list.c \
				store_env/store_env_list.c \
				store_env/store_path.c \


################################################################################
#                                    COlORS                                    #
################################################################################

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
	$(1) 2> $@.log; \
	RESULT=$$?; \
	if [ $$RESULT -ne 0 ] || [ -s $@.log ]; then \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
	else  \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
	fi; \
	cat $@.log; \
	rm -f $@.log 2> /dev/null; \
	exit $$RESULT
endef

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

################################################################################
#                                   COMMANDS                                   #
################################################################################

all: $(OBJS_PATH) $(LIBFT) $(NAME)

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(sort $(dir $(OBJECTS)))

$(NAME): $(LIBFT) $(OBJS)
	@$(call run_and_test, $(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIB_PATH) -lft -lreadline)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIB_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(call run_and_test, $(CC) $(CFLAGS) $(INCS) -c $< -o $@)

clean:
	@$(call run_and_test, rm -rf $(OBJS_PATH))
	@$(MAKE) --no-print-directory -C $(LIB_PATH) clean

fclean:
	@$(call run_and_test, rm -rf $(OBJS_PATH))
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIB_PATH) fclean

re: fclean all

.PHONY: all clean fclean re