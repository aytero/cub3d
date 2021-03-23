/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:03:20 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/23 23:08:24 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	fill(t_all *all)
{
	int 	ceiling_end;
	int 	y;
	int 	x;

	ceiling_end = all->res_y / 2;
	y = -1;
	while (++y < ceiling_end)
	{
		x = -1;
		while (++x < all->res_x)
			all->buf[y][x] = all->fc_color[1];
	}
	while (++y < all->res_y - 1)
	{
		x = -1;
		while (++x < all->res_x)
			all->buf[y][x] = all->fc_color[0];
	}
}
