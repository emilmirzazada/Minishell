# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 18:36:17 by emirzaza          #+#    #+#              #
#    Updated: 2023/09/10 11:55:46 by emirzaza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

D_CHR 	= 	chr/
D_STR 	= 	str/
D_MEM 	= 	mem/
D_NBR 	= 	nbr/
D_GNL 	= 	gnl/
D_LST 	= 	lst/

SOURCES = 			$(D_CHR)ft_isalpha.c \
					$(D_CHR)ft_isdigit.c \
					$(D_CHR)ft_isalnum.c \
					$(D_CHR)ft_isascii.c \
					$(D_CHR)ft_isprint.c \
					$(D_CHR)ft_toupper.c \
					$(D_CHR)ft_tolower.c \
					$(D_MEM)ft_memset.c \
					$(D_MEM)ft_bzero.c \
					$(D_MEM)ft_memcpy.c \
					$(D_MEM)ft_memmove.c \
					$(D_MEM)/ft_memchr.c \
					$(D_MEM)ft_memcmp.c \
					$(D_MEM)ft_calloc.c \
					$(D_MEM)ft_pcalloc.c \
					$(D_STR)ft_strlcpy.c \
					$(D_STR)ft_strlcat.c \
					$(D_STR)ft_strchr.c \
					$(D_STR)ft_strrchr.c \
					$(D_STR)ft_strncmp.c \
					$(D_STR)ft_strnstr.c \
					$(D_STR)ft_strlen.c \
					$(D_STR)ft_strdup.c \
					$(D_STR)ft_substr.c \
					$(D_STR)ft_strjoin.c \
					$(D_STR)ft_strtrim.c \
					$(D_STR)ft_split.c \
					$(D_STR)ft_strmapi.c \
					$(D_STR)ft_striteri.c \
					$(D_STR)ft_putchar_fd.c \
					$(D_STR)ft_putstr_fd.c \
					$(D_STR)ft_putendl_fd.c \
					$(D_STR)ft_putnbr_fd.c \
					$(D_NBR)ft_itoa.c \
					$(D_NBR)ft_atoi.c \
					$(D_GNL)gnl.c \
					$(D_GNL)gnl_utils.c \
					$(D_LST)ft_lstnew.c \
					$(D_LST)ft_lstadd_front.c \
					$(D_LST)ft_lstadd_back.c \
					$(D_LST)ft_lstsize.c \
					$(D_LST)ft_lstlast.c \
					$(D_LST)ft_lstdelone.c \
					$(D_LST)ft_lstclear.c \
					$(D_LST)ft_lstiter.c \
					$(D_LST)ft_lstmap.c \

OBJECTS = $(SOURCES:.c=.o)
# This takes the .c files keeps their names and adds a .o

all: $(NAME)
# this target is run when you just type "make"

$(NAME): $(OBJECTS)
	@ar rcs $@ $^
# $@ is the NAME, $^ will be all the $(OBJECTS)

%.o: %.c
	@$(CC) $(CFLAGS) -I. -c $< -o $@
# $< will be only the first prerequisite

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
# .Phony targets are targets that don't represent files (clean, fclean etc.)