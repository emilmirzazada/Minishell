# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 23:31:04 by emirzaza          #+#    #+#              #
#    Updated: 2023/09/10 11:29:33 by emirzaza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC =	src/main.c \
		src/signals/signals.c \
		src/builtins/env.c \
		parser/parse.c \
		parser/special_chr_check.c 

LIBFT = ./libft
READLINE_PATH = ${PWD}/readline
RM = rm -rf
CC = gcc
CFLAGS = -g -Wall -Wextra -fsanitize=address
OBJ = $(SRC:.c=.o)


UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
    LIBREADLINE_FLAGS = -lreadline -lhistory
else ifeq ($(UNAME),Darwin)
    LIBREADLINE_FLAGS = -I${READLINE_PATH}/include -L${READLINE_PATH}/lib -lreadline -lhistory -ltermcap
endif


all: ${LIBFT} ${NAME}

${NAME}: ${OBJ} ${LIBFT}
	@$(CC) ${CFLAGS} $(OBJ) -o $(NAME) libft.a $(LIBREADLINE_FLAGS)
	@echo "${NAME} compiled"

${LIBFT}:
	@make -q -C libft || make -C libft
	@cp ${LIBFT}/libft.a .
	@echo "libft compiled\n"

%.o: %.c
	@${CC} ${CFLAGS} -I./readline -I./libft -I./includes -c $< -o $@

clean:
	@make clean -C libft
	@${RM} libft.a
	@${RM} ${OBJ}
	@echo "Cleaned"

fclean: clean
	@${RM} ${NAME}
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re ${LIBFT}
