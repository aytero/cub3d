#include "cub3d.h"

void 	buf_pixel(t_all *all, int x, int y, int color)
{
	char	*dst;

	dst = (char *)all->buf + (y * all->line_len + x * (all->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}