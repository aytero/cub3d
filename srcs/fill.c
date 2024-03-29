#include "cub3d.h"

void	fill_img(t_all *all)
{
	int		y;
	int		x;

	y = 0;
	while (y < all->res_y)
	{
		x = 0;
		while (x < all->res_x)
		{
			all->img.addr[all->img.line_len / 4 * y + x] = all->buf[y][x];
			x++;
		}
		y++;
	}
}

void	fill_solid(t_all *all)
{
	int		ceiling_end;
	int		y;
	int		x;

	ceiling_end = all->res_y / 2 - 1;
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
