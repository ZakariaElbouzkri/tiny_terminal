NAME = minishell

CC = cc -Wall -Wextra -Werror -g

RM = rm -f

RDL = -lreadline -L/Users/zel-bouz/.brew/opt/readline/lib/ -lhistory -I/Users/zel-bouz/.brew/opt/readline/include

INC = minishell.h libft/libft.h 

SRC = libft/abs.c libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c \
	libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_isspace.c \
	libft/ft_itoa.c libft/ft_lstadd_back.c libft/ft_lstadd_front.c libft/ft_lstclear.c \
	libft/ft_lstdelone.c libft/ft_lstiter.c libft/ft_lstlast.c libft/ft_lstmap.c libft/ft_lstnew.c \
	libft/ft_lstsize.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c \
	libft/ft_printf.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c \
	libft/ft_split.c libft/ft_strchr.c libft/ft_strcmp.c libft/ft_strdup.c \
	libft/ft_strichr.c libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c \
	libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c \
	libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c \
	libft/get_next_line.c libft/get_next_line_utils.c libft/mandatory_utils.c libft/max.c libft/min.c \
	main.c parse_env.c pipex.c \
	builtins/cd.c builtins/echo.c builtins/env.c builtins/export.c builtins/export2.c builtins/pwd.c builtins/unset.c \
	exec/exec_commands.c exec/exec_herdocs.c exec/execute.c exec/init_redirections.c \
	lexer/check_errors.c lexer/cmd_construct.c lexer/expander.c lexer/join_words.c lexer/lexer.c lexer/lexer_utils.c \
	exec/exec_utils.c exec/exec_pipes.c ft_put_error.c 


OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(RDL) $^ -o $@

%.o : %.c $(INC)
	$(CC) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re 