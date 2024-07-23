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

NAME	= minitalk

CLIENT	= client

SERVER	= server

SRCS	=	client.c \
			server.c \

LIBFT	= ./libft/libft.a

OBJS	= ${SRCS:.c=.o}

OBJS_CLIENT	= client.o

OBJS_SERVER	= server.o

INCLUDES	= -I ./ -I ./libft

AR	= ar rcs

RM	= rm -f

GCC	= gcc

CFLAGS	= -Wall -Werror -Wextra

all: ${CLIENT} ${SERVER}

${LIBFT}:
	make -C libft

${CLIENT}: ${OBJS_CLIENT} ${LIBFT}
	${GCC} ${CFLAGS} ${OBJS_CLIENT} ${LIBFT} -o ${CLIENT}

${SERVER}: ${OBJS_SERVER} ${LIBFT}
	${GCC} ${CFLAGS} ${OBJS_SERVER} ${LIBFT} -o ${SERVER}

%.o: %.c
	${GCC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean:
	${RM} ${OBJS}
	make -C libft clean

fclean:	clean
	${RM} ${CLIENT} ${SERVER}
	make -C libft clean

re:	fclean all

.PHONY:	all clean fclean re