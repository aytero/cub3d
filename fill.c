/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:03:20 by lpeggy            #+#    #+#             */
/*   Updated: 2021/02/10 19:03:22 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	fill(t_all *all)
{
	int 	ceiling_end = all->win_height / 2;
	int 	y = -1;
	int 	x;


	while (y++ < ceiling_end)
	{
		x = -1;
		while (x++ < all->win_width)
			pixel_put(all, x, y, 0xb0b0b0);
	}
	while (++y < all->win_height)
	{
		x = -1;
		while (x++ < all->win_width)
			pixel_put(all, x, y, 0x525252);
	}
}
