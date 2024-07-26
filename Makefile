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

CLIENT_BONUS = client_bonus

SERVER_BONUS = server_bonus

SRCS_CLIENT	= client.c

SRCS_SERVER = server.c

SRCS_CLIENT_BONUS = client_bonus.c

SRCS_SERVER_BONUS = server_bonus.c

LIBFT_DIR = libft

LIBFT	= ${LIBFT_DIR}/libft.a

OBJS_CLIENT	= ${SRCS_CLIENT:.c=.o}

OBJS_SERVER	= ${SRCS_SERVER:.c=.o}

OBJS_CLIENT_BONUS = ${SRCS_CLIENT_BONUS:.c=.o}

OBJS_SERVER_BONUS = ${SRCS_SERVER_BONUS:.c=.o}

INCLUDES	= -I ./ -I ${LIBFT_DIR}

AR	= ar rcs

RM	= rm -f

GCC	= gcc

CFLAGS	= -Wall -Werror -Wextra

all: ${CLIENT} ${SERVER}
bonus: ${CLIENT_BONUS} ${SERVER_BONUS}

${LIBFT}:
	make -C ${LIBFT_DIR}

${CLIENT}: ${OBJS_CLIENT} ${LIBFT}
	${GCC} ${CFLAGS} ${OBJS_CLIENT} ${LIBFT} -o ${CLIENT}

${SERVER}: ${OBJS_SERVER} ${LIBFT}
	${GCC} ${CFLAGS} ${OBJS_SERVER} ${LIBFT} -o ${SERVER}

${CLIENT_BONUS}: ${OBJS_CLIENT_BONUS} ${LIBFT}
	${GCC} ${CFLAGS} ${OBJS_CLIENT_BONUS} ${LIBFT} -o ${CLIENT_BONUS}

${SERVER_BONUS}: ${OBJS_SERVER_BONUS} ${LIBFT}
	${GCC} ${CFLAGS} ${OBJS_SERVER_BONUS} ${LIBFT} -o ${SERVER_BONUS}

%.o: %.c
	${GCC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean:
	${RM} ${OBJS_CLIENT} ${OBJS_SERVER}
	${RM} ${OBJS_CLIENT_BONUS} ${OBJS_SERVER_BONUS}
	make -C ${LIBFT_DIR} clean

fclean:	clean
	${RM} ${CLIENT} ${SERVER} ${CLIENT_BONUS} ${SERVER_BONUS}
	make -C ${LIBFT_DIR} clean

re:	fclean all

.PHONY:	all clean fclean re

# NO_BONUS
# NAME	= minitalk

# CLIENT	= client

# SERVER	= server

# SRCS_CLIENT	= client.c

# SRCS_SERVER = server.c

# LIBFT_DIR = libft

# LIBFT	= ${LIBFT_DIR}/libft.a

# OBJS_CLIENT	= ${SRCS_CLIENT:.c=.o}

# OBJS_SERVER	= ${SRCS_SERVER:.c=.o}

# INCLUDES	= -I ./ -I ${LIBFT_DIR}

# AR	= ar rcs

# RM	= rm -f

# GCC	= gcc

# CFLAGS	= -Wall -Werror -Wextra

# all: ${CLIENT} ${SERVER}

# ${LIBFT}:
# 	make -C ${LIBFT_DIR}

# ${CLIENT}: ${OBJS_CLIENT} ${LIBFT}
# 	${GCC} ${CFLAGS} ${OBJS_CLIENT} ${LIBFT} -o ${CLIENT}

# ${SERVER}: ${OBJS_SERVER} ${LIBFT}
# 	${GCC} ${CFLAGS} ${OBJS_SERVER} ${LIBFT} -o ${SERVER}

# %.o: %.c
# 	${GCC} ${CFLAGS} ${INCLUDES} -c $< -o $@

# clean:
# 	${RM} ${OBJS_CLIENT} ${OBJS_SERVER}
# 	make -C ${LIBFT_DIR} clean

# fclean:	clean
# 	${RM} ${CLIENT} ${SERVER}
# 	make -C ${LIBFT_DIR} clean

# re:	fclean all

# .PHONY:	all clean fclean re