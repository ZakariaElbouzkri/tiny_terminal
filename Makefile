NAME = minishell

LIBFT = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar -rc 

READLINE_DIR = $(shell brew --prefix readline)
RDL = -L$(READLINE_DIR)/lib  -lreadline  
RDL_INC = -I$(READLINE_DIR)/include

INC = minishell.h libft/libft.h 

SRC = parsing/check_errors.c parsing/cmd_construct.c parsing/expander.c  parsing/parsing_utils.c\
	parsing/join_words.c parsing/lexer.c parsing/lexer_utils.c parsing/parse_env.c parsing/parsing_utils2.c\
	parsing/garbage_collector.c execution/exec_commands.c execution/exec_utils.c execution/exec_utils3.c execution/execute.c \
	execution/execute_pipes.c execution/open_herdocs.c execution/open_redirs.c execution/exec_utils4.c \
	builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c \
	builtins/export2.c builtins/pwd.c builtins/unset.c  builtins/cd_utils.c main.c 

LIB = libft/abs.c libft/ft_isascii.c libft/ft_lstadd_front.c libft/ft_lstnew.c libft/ft_memset.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strnstr.c libft/get_next_line.c \
	libft/ft_atoi.c libft/ft_isdigit.c libft/ft_lstclear.c  libft/ft_lstsize.c libft/ft_printf.c libft/ft_strchr.c  libft/ft_strlcat.c  libft/ft_strrchr.c libft/get_next_line_utils.c \
	libft/ft_bzero.c libft/ft_isprint.c libft/ft_lstdelone.c  libft/ft_memchr.c libft/ft_putchar_fd.c libft/ft_strcmp.c  libft/ft_strlcpy.c libft/ft_strtrim.c libft/mandatory_utils.c \
	libft/ft_calloc.c libft/ft_isspace.c libft/ft_lstiter.c  libft/ft_memcmp.c libft/ft_putendl_fd.c libft/ft_strdup.c  libft/ft_strlen.c  libft/ft_substr.c libft/max.c \
	libft/ft_isalnum.c libft/ft_itoa.c libft/ft_lstlast.c libft/ft_memcpy.c libft/ft_putnbr_fd.c libft/ft_strichr.c libft/ft_strmapi.c  libft/ft_tolower.c libft/min.c \
	libft/ft_isalpha.c libft/ft_lstadd_back.c libft/ft_lstmap.c  libft/ft_memmove.c libft/ft_putstr_fd.c libft/ft_striteri.c  libft/ft_strncmp.c  libft/ft_toupper.c 



OBJ = $(SRC:.c=.o)
LIB_OBJ = $(LIB:.c=.o)
LIBFT = libft/libft.a

all : $(LIBFT) $(NAME)

$(LIBFT) : $(LIB_OBJ)
	@$(AR) $@ $^
	@echo "libft created"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(RDL) $(RDL_INC)  $^ $(LIBFT) -o $@
	@echo "$@ created"

%.o : %.c $(INC)
	@$(CC) $(CFLAGS) $(RDL_INC)  -c $< -o $@

clean:
	@$(RM) $(OBJ) $(LIB_OBJ)
	@echo	"object files removed"

fclean: clean
	@$(RM) $(NAME) $(LIBFT)
	@echo	"$(NAME) removed"

re: fclean all

.PHONY: clean fclean all re 
