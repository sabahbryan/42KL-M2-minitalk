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

SRCS_CLIENT	= client.c

SRCS_SERVER = server.c

LIBFT_DIR = libft

LIBFT	= ${LIBFT_DIR}/libft.a

OBJS_CLIENT	= ${SRCS_CLIENT:.c=.o}

OBJS_SERVER	= ${SRCS_SERVER:.c=.o}

INCLUDES	= -I ./ -I ${LIBFT_DIR}

AR	= ar rcs

RM	= rm -f

GCC	= gcc

CFLAGS	= -Wall -Werror -Wextra

all: ${CLIENT} ${SERVER}

${LIBFT}:
	make -C ${LIBFT_DIR}

${CLIENT}: ${OBJS_CLIENT} ${LIBFT}
	${GCC} ${CFLAGS} ${OBJS_CLIENT} ${LIBFT} -o ${CLIENT}

${SERVER}: ${OBJS_SERVER} ${LIBFT}
	${GCC} ${CFLAGS} ${OBJS_SERVER} ${LIBFT} -o ${SERVER}

%.o: %.c
	${GCC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean:
	${RM} ${OBJS_CLIENT} ${OBJS_SERVER}
	make -C ${LIBFT_DIR} clean

fclean:	clean
	${RM} ${CLIENT} ${SERVER}
	make -C ${LIBFT_DIR} clean

re:	fclean all

.PHONY:	all clean fclean re

# NAME = minitalk
# CLIENT = client
# SERVER = server
# LIBFT_DIR = libft
# LIBFT = $(LIBFT_DIR)/libft.a

# CC = gcc
# CFLAGS = -Wall -Wextra -Werror
# INCLUDES = -I ./ -I $(LIBFT_DIR)

# SRCS_CLIENT = client.c
# SRCS_SERVER = server.c

# OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
# OBJS_SERVER = $(SRCS_SERVER:.c:.o)

# all: $(CLIENT) $(SERVER)

# $(LIBFT):
# 	make -C $(LIBFT_DIR)

# $(CLIENT): $(OBJS_CLIENT) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) -o $(CLIENT)

# $(SERVER): $(OBJS_SERVER) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) -o $(SERVER)

# %.o: %.c
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# clean:
# 	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)
# 	make -C $(LIBFT_DIR) clean

# fclean: clean
# 	rm -f $(CLIENT) $(SERVER)
# 	make -C $(LIBFT_DIR) fclean

# re: fclean all

# .PHONY: all clean fclean re
