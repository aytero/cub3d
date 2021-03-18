/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:18:08 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/15 18:18:10 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	sprite_sort(t_all *all)
{
	int 	i;
	int 	j;
	double	tmp;

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
	all->sprt.modif_x = inv_det * (all->plr_dir_y * all->sprt.sprite_x
										- all->plr_dir_x * all->sprt.sprite_y);
	all->sprt.modif_y = inv_det * (-all->plane_y * all->sprt.sprite_x
										+ all->plane_x * all->sprt.sprite_y);
	all->sprt.screen_x = (int)((all->res_x / 2.0)
			* (1.0 + all->sprt.modif_x / all->sprt.modif_y));
	//sprite height
	all->sprt.height = (int)fabs((all->res_y / all->sprt.modif_y));
	all->sprt.draw_start_y = all->res_y / 2 - all->sprt.height / 2;
	all->sprt.draw_end_y = all->res_y / 2 + all->sprt.height / 2;
	if (all->sprt.draw_start_y < 0)
		all->sprt.draw_start_y = 0;
	if (all->sprt.draw_end_y >= all->res_y)
		all->sprt.draw_end_y = all->res_y - 1;
	//sprite width
	all->sprt.width = (int)fabs((all->res_y / all->sprt.modif_y));
	all->sprt.draw_start_x =  all->sprt.screen_x - all->sprt.width / 2;
	all->sprt.draw_end_x = all->sprt.screen_x + all->sprt.width / 2;
	if (all->sprt.draw_start_x < 0)
		all->sprt.draw_start_x = 0;
	if (all->sprt.draw_end_x >= all->res_x)
		all->sprt.draw_end_x = all->res_x - 1;
}

void 	sprite_draw(t_all *all)
{
	int				tex_x;
	int				tex_y;
	int				d;
	unsigned int	color;
	int 	tmp;

	//loop through every vertical stripe
	while (all->sprt.draw_start_x++ <= all->sprt.draw_end_x)
	{
		tex_x = (int) (256 * (all->sprt.draw_start_x
				- (-all->sprt.width / 2 + all->sprt.screen_x)) * all->tex[all->tex_id].width
				/ all->sprt.width) / 256;
		if (all->sprt.modif_y > 0
			&& all->sprt.draw_start_x < all->res_x
			&& all->sprt.draw_start_x >= 0
			&& all->sprt.modif_y < all->sprt.depth_buf[all->sprt.draw_start_x])
		{
			//loop for every pixel of the stripe
			tmp = all->sprt.draw_start_y;
			while (tmp++ < (all->sprt.draw_end_y - 1))
			{
				//printf("y %d\n", all->sprt.draw_start_y);
				d = tmp * 256 - all->res_y * 128 + all->sprt.height * 128;
				tex_y = ((d * all->tex[all->tex_id].height) / all->sprt.height) / 256;
				color = all->tex[all->tex_id].addr[all->tex[all->tex_id].height * tex_y + tex_x];
				//skip invisible pixel
				if ((color & 0x00FFFF) != 0)
					all->buf[tmp][all->sprt.draw_start_x] = color;
			}
		}
	}
}

void 	sprite(t_all *all)
{
	int		i;
//	static	int	counter = 0;

	tmp_init_sprite(all);
	i = -1;
	while (++i < all->sprt.nbr_sprites)
	{
		all->sprt.order[i] = i;
		all->sprt.dist[i] = pow(all->plr_x - all->sprt_cords[i].x, 2)
							+ pow(all->plr_y - all->sprt_cords[i].y, 2);
	}
	sprite_sort(all);
//	find_tex_id(all);
	all->tex_id = 4;//
	i = -1;
	while (++i < all->sprt.nbr_sprites)
	{
		sprite_calc(all, i);
		sprite_draw(all);
	}
//	counter++;
//	printf("cntr  %d\n", counter);
	free(all->sprt.order);
	free(all->sprt.dist);
	//i = 0;
	//while (i++ < all->sprt.nbr_sprites)
	//free(all->sprt.depth_buf);
	free(all->sprt_cords);
}
