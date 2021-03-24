/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:38:40 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/24 03:22:20 by ayto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft/libft.h"

# define SPEED 0.1
# define DOWN 125
# define UP 126
# define LEFT 123
# define RIGHT 124
# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53

typedef struct	s_sprt_cords
{
	double		x;
	double		y;
}				t_sprt_cords;

typedef struct	s_sprite
{
	int 		nbr_sprt;
	int 		*order;
	double 		*dist;
	double		sprite_x;
	double		sprite_y;
	double		modif_x;
	double		modif_y;
	int			screen_x;
	int			start_y;
	int 		end_y;
	int 		start_x;
	int 		end_x;
	int			height;
	int			width;
}				t_sprite;

typedef struct 	s_img
{
	void		*img;
	int 		width;
	int 		height;
	int 		*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
}				t_img;

typedef struct	s_all
{
	void		*mlx;
	void		*win;
	int			res_x;
	int			res_y;
	int 		x;
	double 		coef;

	int			fc_color[2];
	char 			*tex_path[5];//mb + defines
	int				cntr;
	int 		map_lines;
	int			max_line_len;
	int 		plr;

	int				keys[6];

	double		plr_x;
	double		plr_y;
	double 		plr_dir_x;
	double 		plr_dir_y;
	double		plane_x;
	double		plane_y;

	double 		camera_x;//x-coordinate in camera space
	double		ray_dir_x;
	double		ray_dir_y;
	int 		map_x;//which box of the map we're in
	int 		map_y;

	double 		side_dist_x;//length of ray from current position to next x or y-side
	double 		side_dist_y;
	double		delta_dist_x;//length of ray from one x or y-side to next x or y-side
	double 		delta_dist_y;
	double 		wall_dist;

	int 		step_x;//what direction to step in x or y-direction (either +1 or -1)
	int 		step_y;
	int 		hit;//was there a wall hit?
	int 		side;//was a NS or a EW wall hit?

	t_img		*tex;
	t_img		img;
	int			**buf;
	int 		tex_id;

	int 		line_height;//height of line to draw on screen
	int 		draw_start;//calculate lowest and highest pixel to fill in current stripe
	int 		draw_end;

	int 		nbr_sprt;
	double		*depth_buf;
	t_sprt_cords	*sprt_cords;
	int 			save;

	char		**map;
}				t_all;

int		find_plr(t_all *all, int y, int x);
void	map_validate(t_all *all);
void 	find_sprites(t_all *all, t_sprite *sprt);
int 			get_color(t_all *all, int x, int y);
void 			create_bmp(t_all *all);
void 			sprite_calc(t_all *all, t_sprite *sprt, int i);
void 			sprite_sort(t_all *all, t_sprite *sprt);
void 			sprite_draw(t_all *all, t_sprite *sprt);
void 			sprite(t_all *all);
void 			fill_buffer(t_all *all, int tex_x, double step);
void			find_tex_id(t_all *all);
void			fill_img(t_all *all);
void			load_image(t_all *all, t_img *tex, char *path);
void			load_texture(t_all *all);
void 			fill(t_all *all);//rename
void 			tex_calc(t_all *all);
void		 	wall_draw_calc(t_all *all);
void 		init(t_all *all);
void			init_rc(t_all *all);
void			cast_rays(t_all *all);
int				exit_cube(t_all *all, char *str);
void			pixel_put(t_all *all, int x, int y, int color);
void			parse_file(t_all *all, char *file);
int 		key_press(int keycode, t_all *all);
int 		key_release(int keycode, t_all *all);
void		move(t_all *all, double angle);
void		move_sideways(t_all *all, double angle);
void		rotate(t_all *all, double angle);

#endif
