# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 11:40:14 by adpachec          #+#    #+#              #
#    Updated: 2023/02/14 10:48:44 by adpachec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= fdf

SRC_DIR			= srcs/
INC_DIR			= ./include/
OBJ_DIR			= obj/

SRC				= fdf.c ft_split.c get_next_line.c get_next_line_utils.c

SRCS			= $(addprefix $(SRC_DIR), $(SRC))

OBJ				= $(SRC:.c=.o)
OBJS			= $(addprefix $(OBJ_DIR), $(OBJ))

CC				= gcc
# CFLAGS			= -fsanitize=address -g
CFLAGS			= -Wall -Wextra -Werror -fsanitize=address -g -Imlx

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx -c $< -o $@ -I $(INC_DIR)

$(NAME): $(OBJS)
# $(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		$(CC) $(CFLAGS) $(OBJS) -lmlx -framework OpenGL \
		-framework AppKit -o $(NAME)
clean:
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean