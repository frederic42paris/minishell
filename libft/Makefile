################################################################################
#                                   VARIABLES                                  #
################################################################################

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

INC = includes

SRCS_PATH = srcs
PRINTF_SRCS_PATH = srcs/ft_printf

OBJS_PATH = .obj/
PRINTF_OBJS_PATH = $(OBJS_PATH)

OBJS = $(SRCS:.c=.o)
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)

D_OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS))
D_PRINTF_OBJS = $(addprefix $(PRINTF_OBJS_PATH)/, $(PRINTF_OBJS))

################################################################################
#                                    SOURCES                                   #
################################################################################

PRINTF_SRCS =	ft_putnbr_hex.c \
				ft_printf.c \
				ft_formats.c \
				ft_format_hex.c \
				ft_count_digits.c \


SRCS =			ft_atoi.c \
				ft_atof.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_strtol.c \
				ft_isspace.c \
\
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
\
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
\
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
\
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_strpbrk.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
\
				get_next_line.c \
				get_next_line_utils.c \

################################################################################
#                                    COlORS                                    #
################################################################################

COM_COLOR   = \033[0;35m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
	$(1) 2> $@.log; \
	RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
	else  \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Lib_Compiling"

################################################################################
#                                   COMMANDS                                   #
################################################################################

.PHONY: all clean fclean re

all: $(NAME)
	@echo > /dev/null

$(NAME): $(OBJS_PATH) $(INC) $(D_PRINTF_OBJS) $(D_OBJS)
	@$(call run_and_test, ar -rcs $(NAME) $(D_OBJS) $(D_PRINTF_OBJS))

$(OBJS_PATH)%.o: $(SRCS_PATH)/%.c
	@$(call run_and_test, $(CC) $(CFLAGS) -o $@ -c $< -I$(INC))

$(PRINTF_OBJS_PATH)%.o: $(PRINTF_SRCS_PATH)/%.c
	@$(call run_and_test, $(CC) $(CFLAGS) -o $@ -c $< -I$(INC))

$(OBJS_PATH):
	@mkdir -p $@

clean:
	@$(call run_and_test, rm -f $(D_OBJS) && rm -rf $(OBJS_PATH))

fclean:
	@$(call run_and_test, rm -f $(D_OBJS) && rm -rf $(OBJS_PATH))
	@rm -f $(NAME)

re: fclean all