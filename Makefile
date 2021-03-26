# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 18:48:41 by lpeggy            #+#    #+#              #
#    Updated: 2021/03/26 21:43:40 by lpeggy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

HEADER = cub3d.h

SRC = cub3d.c\
	   parse.c\
	   parse_map.c\
	   get_configs.c\
	   map_validate.c\
	   check_utils.c\
	   deal_key.c\
	   exit_cube.c\
	   pixel_get_put.c\
	   cast_rays.c\
	   fill_img.c\
	   textures.c\
	   sprite.c\
	   bitmap.c\
	   init.c

OBJ = $(SRC:.c=.o)

CC = gcc

LIBFT = $(LIBFTDIR)libft.a

MLX = $(MLXDIR)libmlx.a

MLXDIR = ./minilibx_opengl/

LIBFTDIR = ./libft/

HEADER = cub3d.h

FLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) -L./minilibx_opengl -framework OpenGL -framework AppKit libmlx.a -lz -L$(LIBFTDIR) -lft $(OBJ) -o $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

$(MLX):
	make -C $(MLXDIR)
	cp $(MLXDIR)libmlx.a ./

#%.o:%.c $(HEADER)
.c.o: $(HEADER)
	$(CC) $(FLAGS) -I ./mlx.h -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	rm -f libmlx.a
	#rm screenshot.bmp
	make fclean -C $(LIBFTDIR)
	make clean -C $(MLXDIR)

re: fclean all
