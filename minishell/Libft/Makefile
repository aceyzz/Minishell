# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cedmulle <42-xvi@protonmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 17:55:29 by cedmulle          #+#    #+#              #
#    Updated: 2024/04/23 17:56:35 by cedmulle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Sources
SRCS =	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_strncpy.c \
	ft_realloc.c \
	ft_strcmp.c

# Objects
OBJS			= ${SRCS:.c=.o}
# Headers
HEAD			= libft.h
# Name
NAME			= libft.a
# Flags
CFLAGS			= -Wall -Werror -Wextra

# Colors
REDD			= \033[1;31m
GRNN			= \033[1;32m
YELL			= \033[1;33m
BLUE			= \033[1;34m
PURP			= \033[1;35m
CYAN			= \033[1;36m
RST				= \033[0m
CLR 			= \033c
D_REDD			= \033[0;31m
D_GRNN			= \033[0;32m
D_YELL			= \033[0;33m
D_BLUE			= \033[0;34m
D_PURP			= \033[0;35m
D_CYAN			= \033[0;36m

all:		${NAME}

.c.o:
	@gcc ${CFLAGS} -I ${HEAD} -c $< -o ${<:.c=.o}
	@echo "$(CLR)-> $(D_GRNN)Compiling $<$(RST)"

${NAME}:	${OBJS}
	@ar -rcs	${NAME} ${OBJS}

clean:
	@rm -f ${OBJS}

fclean:	clean
	@rm -f ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
