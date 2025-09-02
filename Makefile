# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 20:33:54 by jomunoz           #+#    #+#              #
#    Updated: 2025/09/01 21:29:46 by jomunoz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = pipex_bonus
CC = cc
CFLAGS = -IInclude -Wall -Wextra -Werror
SRC = src/pipex.c src/errors_and_frees.c \
    libft_helpers/ft_split.c libft_helpers/ft_strjoin.c \
    libft_helpers/ft_strnstr.c libft_helpers/ft_strlen.c \
	libft_helpers/ft_strncmp.c libft_helpers/ft_strdup.c\

SRC_BONUS = src_bonus/pipex_bonus.c src_bonus/execute_children_bonus.c \
	src_bonus/path_bonus.c src_bonus/error_handling_bonus.c \
    libft_helpers/ft_split.c libft_helpers/ft_strjoin.c \
    libft_helpers/ft_strnstr.c libft_helpers/ft_strlen.c \
	libft_helpers/ft_strncmp.c libft_helpers/get_next_line.c \
	
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

OBJ_BONUS = $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS)

$(BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BONUS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus