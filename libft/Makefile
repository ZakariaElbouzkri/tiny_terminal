# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asettar <asettar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 22:51:57 by asettar           #+#    #+#              #
#    Updated: 2023/07/08 01:12:24 by asettar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c  ft_isalpha.c ft_isascii.c ft_isdigit.c  \
		ft_isprint.c ft_itoa.c  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_strrchr.c \
		ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c  \
		ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_substr.c  \
		ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_tolower.c ft_toupper.c ft_strtrim.c \
		get_next_line.c get_next_line_utils.c ft_printf.c mandatory_utils.c ft_isspace.c \
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c  \
		ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c min.c max.c abs.c
		
OBJS = ${SRCS:.c=.o}
BOBJS = ${BSRCS:.c=.o}
NAME = libft.a

all : ${NAME}
${NAME} : ${OBJS}
	@ ar rcs $@ $^
%.o : %.c  ../../includes/libft.h
	@ ${CC} ${CFLAGS} -c -o $@ $<
clean :
	@ rm -f ${OBJS} ${BOBJS}
fclean : clean
	@ rm -f ${NAME}
re : fclean all
