/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:38:40 by lpeggy            #+#    #+#             */
/*   Updated: 2021/02/12 16:57:07 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
//# include "libft/get_next_line.h"
# include "libft/libft.h"

# define SPEED 0.2
# define DOWN 125
# define UP 126
# define LEFT 123
# define RIGHT 124
# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define BUFFER_SIZE 4096
# define HEIGHT 540
# define WIDTH 600

typedef struct		s_lst
{
	int				fd;
	char			*reminder;
	int				content;
	struct s_lst	*next;
}					t_lst;

typedef struct	s_sprt_cords
{
	double		x;
	double		y;
}				t_sprt_cords;

typedef struct	s_sprite
{
	int 		nbr_sprites;
	int 		*order;
	double 		*dist;
	double		*depth_buf;
	double sprite_x;
	double sprite_y;
//	double inv_det;
	double transform_x;
	double transform_y;
	int screen_x;
	int draw_start_y;
	int draw_end_y;
	int draw_start_x;
	int draw_end_x;
	int height;
	int width;
	//int tex_x;
	//int tex_y;
//	int d;
//	unsigned int color;
}					t_sprite;

typedef struct 	s_tex
{
	//int 		*texture;
	void		*img;
	int 		img_width;
	int 		img_height;
	int 		*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
}				t_tex;

typedef struct	s_all
{
	void		*mlx;
	void		*win;
	void		*img;
	int 		img_width;
	int 		img_height;
	int 		*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	int			win_width;
	int			win_height;
	int 		x;
	int 		y;

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
	double 		perp_wall_dist;

	int 		step_x;//what direction to step in x or y-direction (either +1 or -1)
	int 		step_y;
	int 		hit;//was there a wall hit?
	int 		side;//was a NS or a EW wall hit?

	t_tex		*tex;
	int 		**texture;
//	int 		texture[TEX_HEIGHT][TEX_WIDTH];
	int 		buf[HEIGHT][WIDTH];
//	int 		**buf;
	int 		tex_id;

	int 		line_height;//height of line to draw on screen
	int 		draw_start;//calculate lowest and highest pixel to fill in current stripe
	int 		draw_end;

	t_sprite	sprt;
	t_sprt_cords	*sprt_cords;

	char		**map;
}				t_all;

void 	sprite_calc(t_all *all, int i);
void 	sprite_sort(t_all *all);
void 	sprite_draw(t_all *all);
void 	tmp_init_sprite(t_all *all);
void 			sprite(t_all *all);
void 	buf_pixel(t_all *all, int x, int y, int color);
void 	fill_buffer(t_all *all, int tex_x, double step);
void	find_tex_id(t_all *all);
void			draw(t_all *all);
void			tex_mem(t_all *all);
void			load_image(t_all *all, t_tex *tex, char *path);
void			load_texture(t_all *all);
void			ft_cleanlst_fd(t_lst **head, int fd);
int				ft_strchr_n(char *s);
t_lst			*ft_lstnew_fd(int fd);
int				get_next_line(int fd, char **line);
void 			fill(t_all *all);
void 			tex_calc(t_all *all);
void		 	draw_calc(t_all *all);
//void			map(t_data *data);
void			cast_rays(t_all *all);
int				deal_key(int keycode, t_all *all);
int				exit_cube(t_all *all);
void			pixel_put(t_all *all, int x, int y, int color);
void			parse_map(t_all *all, char *file);

#endif
