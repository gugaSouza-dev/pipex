# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gusouza- <gusouza-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 22:14:04 by gusouza-          #+#    #+#              #
#    Updated: 2023/01/06 22:14:13 by gusouza-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex
HEADERS_LIST	=	pipex.h
SOURCES_LIST	=	pipex.c exec_command.c command_review.c error.c
OBJS			=	$(SOURCES_LIST:.c=.o)
LIBFT			=	${LIBFT_DIR}libft.a
LIBFT_DIR		=	./libft/
CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra

all: ${NAME}

libft: ${LIBFT}

${NAME}:		${LIBFT} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${INCLUDES} -o ${NAME}
	@echo "Pipex created successfully!"


${LIBFT}:
	clear && make -sC ${LIBFT_DIR}

clean:
	clear
	@make -sC ${LIBFT_DIR} clean
	@echo "Removing pipex objects..."
	@rm -rf ${OBJS}

fclean: clean
	@echo "Removing Libft..."
	@rm -rf ${LIBFT}
	@echo "Libft removed successfully!"
	@echo "Removing pipex..."
	@rm -rf ${NAME}
	@echo "Pipex removed successfully!"

re:	fclean all

.PHONY:		all, clean, fclean, re
