# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 20:33:54 by jomunoz           #+#    #+#              #
#    Updated: 2025/08/12 20:05:09 by jomunoz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -IInclude #-Wall -Wextra -Werror
SRC = src/pipex.c src/children.c src/find.c \
    libft_helpers/ft_split.c libft_helpers/ft_strjoin.c \
    libft_helpers/ft_strnstr.c libft_helpers/ft_strlen.c \
	ft_printf/ft_printf.c ft_printf/ft_printf_util1.c \
	ft_printf/ft_printf_util2.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

r:
	make re && clear && ./pipex

.PHONY: all clean fclean re

# NAME = pipex
# CC = cc
# CFLAGS = -IInclude -Wall -Werror -Wextra
# SRC = pipex.c ft_split.c helper.c find.c children.c \
# 	libft_helpers/ft_split.c libft_helpers/ft_strjoin.c libft_helpers/ft_strnstr.c \
# 	libft_helpers/ft_strlen.c

# SRCOBJ = obj/
# OBJ = $(SRC:.c=.o)
# OBJ := $(addprefix $(SRCOBJ),$(OBJ))

# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# obj/%.o: %.c
# 	@mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -rf obj

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re