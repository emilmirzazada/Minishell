# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 23:31:04 by emirzaza          #+#    #+#              #
#    Updated: 2023/10/25 11:41:00 by emirzaza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC =	main \
		signals/signals \
		cleaner/free_mini \
		cleaner/free_lists \
		executor/executor \
		executor/find_executable \
		executor/heredoc \
		executor/pipes \
		executor/program_executor \
		executor/builtin_executor \
		executor/std_io_utils \
		builtins/env \
		builtins/env_tools \
		builtins/cd \
		builtins/unset \
		builtins/pwd \
		builtins/echo \
		builtins/export \
		builtins/export_echo \
		builtins/exit \
		tokenizer/tokenizer \
		tokenizer/expansion \
		tokenizer/expansion_utils \
		splitter/split \
		splitter/split_quotes \
		splitter/split_tools \
		splitter/split_redirects \
		parser/parse_tokens \
		parser/parse_redir_tokens \
		parser/parse_cmd_tokens 


OBJ_DIR = obj/
SRC_DIR = src/

LIBFT = ./libft
READLINE_PATH = ${PWD}/readline
RM = rm -rf
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))


UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
    LIBREADLINE_FLAGS = /lib/x86_64-linux-gnu/libreadline.so.8
else ifeq ($(UNAME),Darwin)
    LIBREADLINE_FLAGS = -I${READLINE_PATH}/include -L${READLINE_PATH}/lib -lreadline -lhistory -ltermcap
endif


all: ${LIBFT} ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	@$(CC) ${CFLAGS} $(OBJS) -o $(NAME) libft.a $(LIBREADLINE_FLAGS)
	@echo "${NAME} compiled"

${LIBFT}:
	@make -q -C libft || make -C libft
	@cp ${LIBFT}/libft.a .
	@echo "libft compiled\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(@D)
	@${CC} ${CFLAGS} -I./readline -I./libft -I./includes -c $< -o $@

clean:
	@make clean -C libft
	@${RM} libft.a
	@${RM} ${OBJS}
	@echo "Cleaned"

fclean: clean
	@${RM} ${NAME}
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re ${LIBFT}
