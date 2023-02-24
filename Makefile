# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 11:40:14 by adpachec          #+#    #+#              #
#    Updated: 2023/02/24 13:34:01 by adpachec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= fdf

SRC_DIR			= srcs/
INC_DIR			= ./include/
OBJ_DIR			= obj/

SRC				= fdf.c ft_split.c get_next_line.c get_next_line_utils.c \
					draw_lines.c error_management.c fdf_utils.c fdf_utils2.c \
					get_max_min.c get_size.c read_map.c read_map2.c \
					rescale_coord.c key_hooks.c gradient_color.c

SRCS			= $(addprefix $(SRC_DIR), $(SRC))

OBJ				= $(SRC:.c=.o)
OBJS			= $(addprefix $(OBJ_DIR), $(OBJ))

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -Imlx

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx -c $< -o $@ -I $(INC_DIR)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -lmlx -framework OpenGL \
		-framework AppKit -o $(NAME)
clean:
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean