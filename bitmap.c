#include "cub3d.h"

static void		int_to_uchar(int n, unsigned char *dst)
{
	dst[0] = (unsigned char)n;
	dst[1] = (unsigned char)n >> 8;
	dst[2] = (unsigned char)n >> 16;
	dst[3] = (unsigned char)n >> 24;
}

static void 	bmp_header(t_all *all, int img_size)
{
	all->bmp[0] = 'B';
	all->bmp[1] = 'M';
	//int to unsigned char
//	bmp[2] = filesize + 54;//54 - offset
	int_to_uchar(img_size + 54, &all->bmp[2]);
//	ft_memset(&all->bmp[2], (int)(img_size + 54), 1);
//	bmp[10] = 54;//pixel data offset
	ft_memset(&all->bmp[10], (int)54, 1);
//	bmp[14] = 40;//header size
	ft_memset(&all->bmp[14], (int)40, 1);
//	bmp[18] = all->win_width;//img width
//	ft_memset(&all->bmp[18], (int)all->win_width, 1);
	int_to_uchar(all->win_width, &all->bmp[18]);
//	bmp[22] = all->win_height;//img height
//	ft_memset(&all->bmp[22], (int)all->win_height, 1);
	int_to_uchar(all->win_height, &all->bmp[22]);

//	bmp[26] = 1;//color plane
	ft_memset(&all->bmp[26], (short)1, 1);
//	bmp[28] = 32;//bits per pixel
	ft_memset(&all->bmp[28], (short)32, 1);
	ft_memset(&all->bmp[34], (int)img_size, 1);
}

int 	create_bmp(t_all *all)
{
	int 	fd;
	int 	img_size;
	int 	x;
	int 	y;
	int 	color;

	img_size = all->win_width * all->win_height * 4;// 4 - bytes per pixel
	if (!(all->bmp = ft_calloc(54, sizeof(unsigned char))))
		return (-1);
//	if (!(all->bmp_color = ft_calloc(img_size, sizeof(unsigned char))))
//		return (-1);
//	all->bmp = malloc(sizeof(unsigned char) * (img_size + 54));
//	ft_memset(all->bmp, 0, (img_size + 54));

	if ((fd = open("screenshot.bmp", O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0664)) < 0)
		return (-1);
	bmp_header(all, img_size);
	write(fd, all->bmp, 54);
	y = all->win_height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < all->win_width)
		{
			color = get_color(all, x, y);
			//printf("%d\n", color);
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
	//write(fd, all->bmp_color, img_size);
	free(all->bmp);
//	free(all->bmp_color);
	close(fd);
	return (0);
}
