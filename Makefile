# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 18:48:41 by lpeggy            #+#    #+#              #
#    Updated: 2021/02/12 17:57:53 by lpeggy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

HEADER = cub3d.h

SRC = cub3d.c\
	   parse.c\
	   deal_key.c\
	   exit_cube.c\
	   pixel_put.c\
	   cast_rays.c\
	   fill.c\
	   get_next_line.c\
	   get_next_line_utils.c\
	   textures.c

SRCO = $(SRC:.c=.o)

CC = gcc

LIBFT = $(LIBFTDIR)libft.a

MLX = $(MLXDIR)libmlx.dylib

MLXDIR = ./minilibx_mms/

LIBFTDIR = ./libft/

HEADER = cub3d.h

FLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(SRCO) $(LIBFT) $(MLX)
	$(CC) -L./minilibx_mms -framework OpenGL -framework AppKit -lmlx -lz -L$(LIBFTDIR) -lft $(SRCO) -o $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

$(MLX):
	make -C $(MLXDIR)
	cp $(MLXDIR)libmlx.dylib ./

%.o:%.c $(HEADER)
	$(CC) $(FLAGS) -I ./mlx.h -c $< -o $@

clean:
	rm -f $(SRCO)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
#	rm -f libmlx.dylib
#	rm -f $(MLXDIR)libmlx.dylib
	make fclean -C $(LIBFTDIR)

re: fclean all
	make clean -C $(MLXDIR)
