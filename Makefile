# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 18:48:41 by lpeggy            #+#    #+#              #
#    Updated: 2021/03/29 18:23:40 by lpeggy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

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
	$(CC) -L$(MLXDIR) -framework OpenGL -framework AppKit libmlx.a -lz -L$(LIBFTDIR) -lft $(OBJS) -o $(NAME)

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