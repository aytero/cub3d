/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_get_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:29:25 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/18 19:29:27 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;

	dst = (char *)all->buf + (y * all->line_len + x
			* (all->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int		get_color(t_all *all, int x, int y)
{
	char	*dst;
	int		color;

	dst = (char *)all->addr + (y * all->line_len + x
			* (all->bits_per_pixel / 8));
	color = *(int *)dst;
	return (color);
}
