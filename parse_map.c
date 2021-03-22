#include "cub3d.h"

void	plr(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	while (i < all->map_lines)
	{
		j = 0;
		while (j < all->max_line_len && all->map[i][j])
		{
			if (all->map[i][j] == 'N' || all->map[i][j] == 'S'
				|| all->map[i][j] == 'W' || all->map[i][j] == 'E')
			{
				all->plr_y = j;
				all->plr_x = i;
			}
			if (all->map[i][j] == '2')
			{
				//all->sprt_cords[all->nbr_sprites].x = i;
				//all->sprt_cords[all->nbr_sprites].y = j;
				all->nbr_sprites++;
			}
			j++;
		}
		i++;
	}
}