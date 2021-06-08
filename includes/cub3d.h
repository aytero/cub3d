#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../minilibx_opengl/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>

# define SPEED 0.08
# define DOWN_KEY 125
# define UP_KEY 126
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define Q_KEY 12
# define E_KEY 14
# define ESC_KEY 53

# define X_SIDE 0
# define Y_SIDE 1

typedef struct s_sprt_pos
{
	double		x;
	double		y;
}				t_sprt_pos;

typedef struct s_sprite
{
	//int			nbr_sprt;
	int			*order;
	double		*dist;
	double		sprite_x;
	double		sprite_y;
	double		modif_x;
	double		modif_y;
	int			screen_x;
	int			start_y;
	int			end_y;
	int			start_x;
	int			end_x;
	int			height;
	int			width;
}				t_sprite;

typedef struct s_rc
{
	double		plr[2];
}				t_rc;

typedef struct s_img
{
	void		*img;
	int			width;
	int			height;
	int			*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	int			x;
	int			keys[256];
	int			save;
	double		coef;
	int			res_x;
	int			res_y;
	int			fc_color[2];
	char		*tex_path[5];
	int			cntr;
	int			map_height;
	int			map_width;
	char		**map;
	int			plr_flag;
	int			map_flag;
//	double		plr_x;
//	double		plr_y;
//	double		plr_dir_x;
//	double		plr_dir_y;
//	double		plane_x;
//	double		plane_y;

	double		plr[2];
	double		plr_dir[2];
	double		plane[2];
	double		ray_dir[2];
//	int			map_cur[2];
	double		side_dist[2];
	double		delta_dist[2];
	int 		step[2];


	double		camera_x;
//	double		ray_dir_x;
//	double		ray_dir_y;
//	int			map_x;
//	int			map_y;
	int 		map_cur[2];
//	double		side_dist_x;
//	double		side_dist_y;
//	double		delta_dist_x;
//	double		delta_dist_y;
	double		wall_dist;
//	int			step_x;
//	int			step_y;
	int			hit;
	int			side;
	t_img		*tex;
	t_img		img;
	int			**buf;
	int			tex_id;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			nbr_sprt;
	double		*depth_buf;
	t_sprt_pos	*sprt_pos;
}				t_all;

void			init_sprites(t_all *all);
void			init_sprites_utils(t_all *all, t_sprite *sprt);
void			sprite_calc(t_all *all, t_sprite *sprt, int i);
void			sprite_sort(t_all *all, t_sprite *sprt);
void			sprite_draw(t_all *all, t_sprite *sprt);
void			sprite(t_all *all);
void			find_tex_id(t_all *all);
void			fill_walls(t_all *all, int tex_x, double step);
void			fill_img(t_all *all);
void			fill_solid(t_all *all);
void			load_image(t_all *all, t_img *tex, char *path);
void			load_texture(t_all *all);
void			tex_calc(t_all *all);
void			wall_draw_calc(t_all *all);
void			init_mlx(t_all *all);
void			init_buf(t_all *all);
void			init_rc(t_all *all);
void			cast_rays(t_all *all);
void			exit_cube(t_all *all, char *str);
int				key_press(int keycode, t_all *all);
int				key_release(int keycode, t_all *all);
void			move(t_all *all, double angle);
void			move_sideways(t_all *all, double angle);
void			rotate(t_all *all, double angle);
int				atoi_color(const char *str);
int				atoi_res(const char *str);
void			create_bmp(t_all *all);

#endif
