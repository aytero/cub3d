/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:18:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/15 18:18:44 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	buf_pixel(t_all *all, int x, int y, int color)
{
	char	*dst;

	dst = (char *)all->buf + (y * all->line_len + x * (all->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
