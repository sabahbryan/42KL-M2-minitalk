# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 16:50:17 by bryaloo           #+#    #+#              #
#    Updated: 2024/07/17 16:50:19 by bryaloo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	=	client.c \
			server.c \

LIBFT	= ./libft/

LIBFT_A = ./libft/libft.a

OBJS	= ${addprefix objs/, ${SRCS:.c=.o}}

AR	= ar rcs

RM	= rm -f

GCC	= gcc

CFLAGS	= -Wall -Werror -Wextra

all: ${NAME}

objs/%.o: %.c
	mkdir -p objs
	${GCC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			make -C ${LIBFT}
			${AR} $@ ${OBJS}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re