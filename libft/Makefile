# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asettar <asettar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 02:30:10 by asettar           #+#    #+#              #
#    Updated: 2023/07/28 01:40:23 by asettar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c  ft_isalpha.c ft_isascii.c ft_isdigit.c  \
		ft_isprint.c ft_itoa.c  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_strrchr.c \
		ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c  \
		ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_substr.c  \
		ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_tolower.c ft_toupper.c ft_strtrim.c \
		get_next_line.c get_next_line_utils.c ft_printf.c mandatory_utils.c \
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_strcmp.c\
		ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c min.c max.c abs.c ft_strichr.c ft_isspace.c 
		
OBJS = ${SRCS:.c=.o}
NAME = libft.a

all : ${NAME}
${NAME} : ${OBJS}
	@ ar rcs $@ $^
%.o : %.c  libft.h
	@ ${CC} ${CFLAGS} -c -o $@ $<
clean :
	@ rm -f ${OBJS}
fclean : clean
	@ rm -f ${NAME}
re : fclean all