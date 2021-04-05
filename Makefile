# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 18:48:41 by lpeggy            #+#    #+#              #
#    Updated: 2021/04/05 18:53:09 by lpeggy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HEADER = cub3d.h

SRCS = ./srcs/cub3d.c\
	   ./srcs/parse.c\
	   ./srcs/map_parse.c\
	   ./srcs/get_configs.c\
	   ./srcs/map_validate.c\
	   ./srcs/init.c\
	   ./srcs/deal_key.c\
	   ./srcs/exit_cube.c\
	   ./srcs/cast_rays.c\
	   ./srcs/fill.c\
	   ./srcs/init_textures.c\
	   ./srcs/sprite.c\
	   ./srcs/utils.c\
	   ./srcs/bitmap.c

OBJS = $(SRCS:.c=.o)

CC = gcc

MLXDIR = ./minilibx_opengl/

LIBFTDIR = ./libft/

LIBFT = $(LIBFTDIR)libft.a

MLX = $(MLXDIR)libmlx.a

FLAGS = -Wall -Werror -Wextra

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
