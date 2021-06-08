#include "cub3d.h"

static int	get_color(t_all *all, int x, int y)
{
	char	*dst;
	int		color;

	dst = (char *)all->img.addr + (y * all->img.line_len
			+ x * (all->img.bits_per_pixel / 8));
	color = *(int *)dst;
	return (color);
}

static void	bmp_colors(t_all *all, int img_size, int fd)
{
	int		x;
	int		y;
	int		*colors;
	int		i;

	colors = malloc(sizeof(int) * img_size);
	if (!colors)
		exit_cube(all, "Memory allocation failed\n");
	i = 0;
	y = all->res_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < all->res_x && i <= img_size)
		{
			colors[i++] = get_color(all, x, y);
			x++;
		}
		y--;
	}
	write(fd, colors, img_size);
	free(colors);
}

static void	cast(int val, unsigned char *dst)
{
	int		i;

	i = -1;
	while (++i < 4)
		dst[i] = (unsigned char)(val >> (i * 8));
}

static void	bmp_header(t_all *all, int img_size, int fd)
{
	unsigned char	*bmp;

	bmp = malloc(sizeof(unsigned char) * 54);
	if (!bmp)
		exit_cube(all, "Memory allocation failed\n");
	ft_memset(bmp, 0, 54);
	bmp[0] = 'B';
	bmp[1] = 'M';
	cast(img_size + 54, &bmp[2]);
	ft_memset(&bmp[10], (int)54, 1);
	ft_memset(&bmp[14], (int)40, 1);
	cast(all->res_x, &bmp[18]);
	cast(all->res_y, &bmp[22]);
	ft_memset(&bmp[26], (short)1, 1);
	ft_memset(&bmp[28], (short)32, 1);
	ft_memset(&bmp[34], (int)img_size, 1);
	write(fd, bmp, 54);
	free(bmp);
}

void	create_bmp(t_all *all)
{
	int		fd;
	int		img_size;

	img_size = all->res_x * all->res_y * 4;
	fd = open("screenshot.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd < 0)
		exit_cube(all, "Failed to create .bmp file\n");
	bmp_header(all, img_size, fd);
	bmp_colors(all, img_size, fd);
	close(fd);
}
