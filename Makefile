# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 20:33:54 by jomunoz           #+#    #+#              #
#    Updated: 2025/08/26 22:31:39 by jomunoz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -IInclude -Wall -Wextra -Werror
SRC = src/pipex.c src/create.c src/execute.c src/path.c src/error_handling.c \
    libft_helpers/ft_split.c libft_helpers/ft_strjoin.c \
    libft_helpers/ft_strnstr.c libft_helpers/ft_strlen.c \
	libft_helpers/ft_strncmp.c libft_helpers/get_next_line.c \
	src/here_doc.c

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

.PHONY: all clean fclean re