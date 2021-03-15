#include "cub3d.h"
#include <unistd.h>

void 	sprite_sort(t_all *all)
{
	int 	i;
	int 	j;
	double	tmp;

	i = -1;
	while (++i < all->sprt.nbr_sprites)
	{
		all->sprt.order[i] = i;
		all->sprt.dist[i] = pow(all->plr_x - all->sprt_cords[i].x, 2)
						+ pow(all->plr_y - all->sprt_cords[i].y, 2);
	}
	i = -1;
	while (++i < all->sprt.nbr_sprites)
	{
		j = -1;
		while (++j < all->sprt.nbr_sprites - 1)
		{
			if (all->sprt.dist[j] < all->sprt.dist[j + 1])
			{
				tmp = all->sprt.dist[j];
				all->sprt.dist[j] = all->sprt.dist[j + 1];
				all->sprt.dist[j + 1] = tmp;
				tmp = all->sprt.order[j];
				all->sprt.order[j] = all->sprt.order[j + 1];
				all->sprt.order[j + 1] = (int)tmp;
			}
		}
	}
}

void 	sprite_calc(t_all *all, int i)
{
	double	inv_det;

	all->sprt.sprite_x = all->sprt_cords[all->sprt.order[i]].x - all->plr_x;
	all->sprt.sprite_y = all->sprt_cords[all->sprt.order[i]].y - all->plr_y;
	//matrix multiplication
	inv_det = 1.0 / (all->plane_x * all->plr_dir_y - all->plr_dir_x * all->plane_y);
	all->sprt.transform_x = inv_det * (all->plr_dir_y * all->sprt.sprite_x - all->plr_dir_x * all->sprt.sprite_y);
	all->sprt.transform_y = inv_det * (-all->plane_y * all->sprt.sprite_x + all->plane_x * all->sprt.sprite_y);

	all->sprt.screen_x = (int)((all->win_width / 2.0) * (1.0 + all->sprt.transform_x / all->sprt.transform_y));

	//sprite height
	all->sprt.height = (int)fabs((all->win_height / all->sprt.transform_y));
	all->sprt.draw_start_y = all->win_height / 2 - all->sprt.height / 2;
	all->sprt.draw_end_y = all->win_height / 2 + all->sprt.height / 2;
	if (all->sprt.draw_start_y < 0)
		all->sprt.draw_start_y = 0;
	if (all->sprt.draw_end_y >= all->win_height)
		all->sprt.draw_end_y = all->win_height - 1;
	//sprite width
	all->sprt.width = (int)fabs((all->win_height / all->sprt.transform_y));
	all->sprt.draw_start_x =  all->sprt.screen_x - all->sprt.width / 2;
	all->sprt.draw_end_x = all->sprt.screen_x + all->sprt.width / 2;
	if (all->sprt.draw_start_x < 0)
		all->sprt.draw_start_x = 0;
	if (all->sprt.draw_end_x >= all->win_width)
		all->sprt.draw_end_x = all->win_width - 1;
}

void 	sprite_draw(t_all *all)
{
	int		tex_x;
	int 	tex_y;
	int		d;
	unsigned int color;

//	find_tex_id(all);
	all->tex_id = 4;//
	//loop through every vertical stripe
//	write(1, "seg\n", 4);//it dies somewhere
//	write(1, "not seg\n", 8);
	while (all->sprt.draw_start_x < all->sprt.draw_end_x)
	{
		tex_x = (int) (256 * (all->sprt.draw_start_x - (-all->sprt.width / 2 + all->sprt.screen_x)) * 64 / all->sprt.width) / 256;
		if (all->sprt.transform_y > 0
			&& all->sprt.draw_start_x < all->win_width
			&& all->sprt.draw_start_x > 0
			&& all->sprt.transform_y < all->sprt.depth_buf[all->sprt.draw_start_x])
		{
			//loop for every pixel of the stripe
			while (all->sprt.draw_start_y < all->sprt.draw_end_y)
			{
				d = all->sprt.draw_start_y * 256 - all->win_height * 128 + all->sprt.height * 128;
				tex_y = ((d * all->tex[all->tex_id].img_height) / all->sprt.height) / 256;
				color = all->tex[all->tex_id].addr[all->tex[all->tex_id].img_height * tex_y + tex_x];
				//skip invisible pixel
				if ((color & 0x00FFFF) != 0)// if color > 0
					all->buf[all->sprt.draw_start_y][all->sprt.draw_start_x] = color;
				all->sprt.draw_start_y++;
			}
		}
		all->sprt.draw_start_x++;
	}
}

void 	sprite(t_all *all)
{
	int		i;

	tmp_init_sprite(all);
	all->sprt.depth_buf[all->x] = all->perp_wall_dist;//need to init arrays

	sprite_sort(all);
	i = -1;
	while (++i < all->sprt.nbr_sprites)
	{
		sprite_calc(all, i);
		sprite_draw(all);//kills processes
	}
}

void 	tmp_init_sprite(t_all *all)
{
	all->sprt.depth_buf = malloc(sizeof(double) * all->win_width);
	all->sprt.order = malloc(sizeof(int) * all->sprt.nbr_sprites);
	all->sprt.dist = malloc(sizeof(double) * all->sprt.nbr_sprites);

	all->sprt_cords = malloc(sizeof(t_sprt_cords) * all->sprt.nbr_sprites);

	all->sprt_cords[0].x = 6;
	all->sprt_cords[0].y = 6;
	all->sprt_cords[1].x = 7;
	all->sprt_cords[1].y = 6;
	all->sprt_cords[2].x = 3;
	all->sprt_cords[2].y = 6;
	all->sprt_cords[3].x = 3.5;
	all->sprt_cords[3].y = 6;

}