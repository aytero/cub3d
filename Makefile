NAME = cub3D

HEADER = ./includes/

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
	   utils.c\
	   bitmap.c

OBJSDIR = ./objs
SRCSDIR = ./srcs
HDRDIR = ./includes
MLXDIR = ./minilibx_opengl
LIBFTDIR = ./libft


LIBFT = $(LIBFTDIR)libft.a

MLX = $(MLXDIR)libmlx.a

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

OBJS = $(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

all: libs $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c $(HEADER)
	@$(CC) $(FLAGS) -I $(HDRDIR) -I $(LIBFTDIR) -I $(MLXDIR) -c $< -o $@

libs:
	@make bonus -C $(LIBFTDIR)
	@make -C $(MLXDIR)

$(NAME): $(OBJSDIR) $(OBJS)
	$(CC) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -lz -L$(LIBFTDIR) -lft $(OBJS) -o $(NAME)

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

bonus: $(NAME)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJSDIR)
	make clean -C $(LIBFTDIR)

fclean:	clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)
	make clean -C $(MLXDIR)

re:		fclean all

.PHONY:	all bonus clean fclean re
