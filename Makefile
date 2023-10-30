# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 23:31:04 by emirzaza          #+#    #+#              #
#    Updated: 2023/10/28 12:37:40 by emirzaza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC =	main \
		signals/signals \
		signals/signal_reset \
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

LIBFT = libft.a
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/$(LIBFT)
READLINE_PATH = ${PWD}/readline
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))


UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
    LIBREADLINE_FLAGS = /lib/x86_64-linux-gnu/libreadline.so.8
else ifeq ($(UNAME),Darwin)
    LIBREADLINE_FLAGS = -I${READLINE_PATH}/include -L${READLINE_PATH}/lib -lreadline -lhistory -ltermcap
endif


all: ${LIBFT_LIB} ${NAME}

${NAME}: ${OBJS} $(LIBFT_LIB)
	@$(CC) ${CFLAGS} $(OBJS) -o $(NAME) $(LIBFT_LIB) $(LIBREADLINE_FLAGS)
	@echo "${NAME} compiled"

${LIBFT_LIB}:
	@make -C libft
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
