#include "cub3d.h"

int 	get_color(t_all *all, int x, int y)
{
	char *dst;
	int color;

	dst = (char *)all->addr + (y * all->line_len + x * (all->bits_per_pixel / 8));
	color = *(int *)dst;
	return (color);
}