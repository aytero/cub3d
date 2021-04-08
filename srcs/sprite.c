/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:18:08 by lpeggy            #+#    #+#             */
/*   Updated: 2021/04/09 00:42:22 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		sprite_sort(t_all *all, t_sprite *sprt)
{
	int		i;
	int		j;
	double	tmp;

	i = -1;
	while (++i < all->nbr_sprt)
	{
		j = -1;
		while (++j < all->nbr_sprt - 1)
		{
			if (sprt->dist[j] < sprt->dist[j + 1])
			{
				tmp = sprt->dist[j];
				sprt->dist[j] = sprt->dist[j + 1];
				sprt->dist[j + 1] = tmp;
				tmp = sprt->order[j];
				sprt->order[j] = sprt->order[j + 1];
				sprt->order[j + 1] = (int)tmp;
			}
		}
	}
}

void		sprite_calc(t_all *all, t_sprite *sprt, int i)
{
	double	inv;

	sprt->sprite_x = all->sprt_pos[sprt->order[i]].x - all->plr_x;
	sprt->sprite_y = all->sprt_pos[sprt->order[i]].y - all->plr_y;
	inv = 1.0 / (all->plane_x * all->plr_dir_y - all->plr_dir_x * all->plane_y);
	sprt->modif_x = inv * (all->plr_dir_y * sprt->sprite_x
										- all->plr_dir_x * sprt->sprite_y);
	sprt->modif_y = inv * (-all->plane_y * sprt->sprite_x
										+ all->plane_x * sprt->sprite_y);
	sprt->screen_x = (int)((all->res_x / 2.0)
					* (1.0 + sprt->modif_x / sprt->modif_y));
	sprt->height = (int)fabs((all->res_y * all->coef / sprt->modif_y));
	sprt->start_y = all->res_y / 2 - sprt->height / 2;
	sprt->end_y = all->res_y / 2 + sprt->height / 2;
	if (sprt->start_y < 0)
		sprt->start_y = 0;
	if (sprt->end_y >= all->res_y)
		sprt->end_y = all->res_y - 1;
	sprt->width = (int)fabs((all->res_y * all->coef / sprt->modif_y));
	sprt->start_x = sprt->screen_x - sprt->width / 2;
	sprt->end_x = sprt->screen_x + sprt->width / 2;
	if (sprt->start_x < 0)
		sprt->start_x = 0;
	if (sprt->end_x >= all->res_x)
		sprt->end_x = all->res_x - 1;
}

static void	sprite_draw_line(t_all *all, t_sprite *sprt, int tex_x, int line)
{
	int		tex_y;
	int		d;
	int		color;
	int		i;

	i = sprt->start_y;
	while (i < sprt->end_y)
	{
		d = i * 256 - all->res_y * 128 + sprt->height * 128;
		tex_y = ((d * all->tex[4].height) / sprt->height) / 256;
		color = all->tex[4].addr[all->tex[4].height * tex_y + tex_x];
		if ((color & 0x00FFFF) != 0)
			all->buf[i][line] = color;
		i++;
	}
}

void		sprite_draw(t_all *all, t_sprite *sprt)
{
	int		tex_x;

	while (sprt->start_x < sprt->end_x)
	{
		tex_x = (int)(256 * (sprt->start_x - (-sprt->width / 2
				+ sprt->screen_x)) * all->tex[4].width / sprt->width) / 256;
		if (sprt->modif_y > 0 && sprt->start_x < all->res_x
		&& sprt->start_x >= 0 && sprt->modif_y < all->depth_buf[sprt->start_x])
			sprite_draw_line(all, sprt, tex_x, sprt->start_x);
		sprt->start_x++;
	}
}

void		sprite(t_all *all)
{
	int			i;
	t_sprite	sprt;

	ft_bzero(&sprt, sizeof(sprt));
	if (!(sprt.order = malloc(sizeof(int) * all->nbr_sprt)))
		exit_cube(all, "Memory allocation failed\n");
	if (!(sprt.dist = malloc(sizeof(double) * all->nbr_sprt)))
		exit_cube(all, "Memory allocation failed\n");
	init_sprites_utils(all, &sprt);
	sprite_sort(all, &sprt);
	i = -1;
	while (++i < all->nbr_sprt)
	{
		sprite_calc(all, &sprt, i);
		sprite_draw(all, &sprt);
	}
	if (sprt.order)
		free(sprt.order);
	if (sprt.dist)
		free(sprt.dist);
}
