#ifndef PARSER_H
# define PARSER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../minilibx_opengl/mlx.h"
# include "../libft/libft.h"
# include "cub3d.h"

void			map_copy(t_all *all, char *str);
void			get_map_size(t_all *all, char *str);
int				map(t_all *all, char *str);
int				get_fc_colors(t_all *all, char *str);
char			*get_texture_path(t_all *all, char *str);
void			get_texture(t_all *all, char *str);
void			get_res(t_all *all, char *str);
void			parse_file(t_all *all, char *file);
void			check_args(t_all *all, int argc, char **argv);
void			map_validate(t_all *all);
int				find_plr(t_all *all, int y, int x);

#endif
