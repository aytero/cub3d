/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:24:23 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/03 04:24:25 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;

	dst = (char *)all->addr + (y * all->line_len + x * (all->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
