#include "cub3d.h"

void 	sort_sprites(t_all *all, int *sprt_buf)
{
	int 	i;

	i = 0;
	while (i < all->num_sprites)
	{
		sprite_order = i;
		sprite_distance = pow(all->plr_x - sprite[i].all->x, 2) + pow(all->plr_y - sprite[i].all->y, 2);
	}
}

void 	sprite(t_all *all)
{
	int 	*sprt_buf;
	int		i;
	double 	sprite_x;
	double 	sprite_y;
	double 	inv_det;
	double	transform_x;
	double	transform_y;
	int 	sprite_screen_x;
	int 	draw_start_y;
	int 	draw_end_y;
	int 	sprt_height;
	int 	draw_start_x;
	int 	draw_end_x;
	int 	sprt_width;

	unsigned int color;

	sprt_buf[all->x] = all->perp_wall_dist;

	sort_sprites(all, sprt_buf);
	i = 0;
	while (i < all->num_sprites)
	{
		sprite_x = sprite[sprite_order[i]].all->x - all->plr_x;
		sprite_y = sprite[sprite_order[i]].all->y - all->plr_y;

		//matrix multiplication
		inv_det = 1.0 / (all->plane_x * all->plr_dir_y - all->plr_dir_x * all->plane_y);
		transform_x = inv_det * (all->plr_dir_y * sprite_x - all->plr_dir_x * sprite_y);
		transform_y = inv_det * (-all->plane_y * sprite_x + all->plane_x * sprite_y);

		sprite_screen_x = (int)((all->win_width / 2) * (1 + transform_x / transform_y));

		//sprite height
		sprt_height = (int)fabs((all->win_height / transform_y));
		draw_start_y = all->win_height / 2 - sprt_height / 2;
		draw_end_y = all->win_height / 2 + sprt_height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		if (draw_end_y >= all->win_height)
			draw_end_y = all->win_height - 1;
		//sprite width
		sprt_width = (int)fabs((all->win_height / transform_y));
		draw_start_x =  sprite_screen_x - sprt_width / 2;
		draw_end_x = sprite_screen_x + sprt_width / 2;
		if (draw_start_x < 0)
			draw_start_x = 0;
		if (draw_end_x >= all->win_width)
			draw_end_x = all->win_width - 1;
		//loop through every vertical stripe
		while (draw_start_x < draw_end_x)
		{
			sprt_tex_x = int(256 * (draw_start_x - (-sprt_width / 2 + sprite_screen_x)) * 64 / sprt_width) / 256;
			if (transform_y > 0 && draw_start_x < all->win_width && transform_y < sprt_buf[draw_start_x])
			//loop for every pixel of the stripe
				while (draw_start_y < draw_end_y)
				{
					d = all->y * 256 - all->win_height * 128 + sprt_height * 128;
					sprt_tex_y = ((d * 64) / sprt_height) / 256;
					color = all->tex[all->tex_id].addr[all->tex[all->tex_id].img_height * sprt_tex_y + sprt_tex_x];
					if ((color & 0x00FFFF) != 0)
						buf[all->y][draw_start_y] = color;
				}
			//skip invisible pixel
			//
		}
	}
}