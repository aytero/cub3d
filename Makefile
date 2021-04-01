# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 18:48:41 by lpeggy            #+#    #+#              #
#    Updated: 2021/04/02 01:17:34 by ayto             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HEADER = cub3d.h

SRCS = cub3d.c\
	   parse.c\
	   map_parse.c\
	   get_configs.c\
	   map_validate.c\
	   init.c\
	   deal_key.c\
	   exit_cube.c\
	   cast_rays.c\
	   fill.c\
	   init_textures.c\
	   sprite.c\
	   bitmap.c

OBJS = $(SRCS:.c=.o)

CC = gcc

MLXDIR = ./minilibx_opengl/

LIBFTDIR = ./libft/

LIBFT = $(LIBFTDIR)libft.a

MLX = $(MLXDIR)libmlx.a

FLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -lz -L$(LIBFTDIR) -lft $(OBJS) -o $(NAME)

$(LIBFT):
	make bonus -C $(LIBFTDIR)

$(MLX):
	make -C $(MLXDIR)
	cp $(MLXDIR)libmlx.a ./

.c.o: $(HEADER)
	$(CC) $(FLAGS) -I ./mlx.h -c $< -o $@

bonus: $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFTDIR)
	make clean -C $(MLXDIR)

fclean:	clean
	rm -f $(NAME)
	rm -f libmlx.a
	make fclean -C $(LIBFTDIR)

re:		fclean all

.PHONY:	all bonus clean fclean re
