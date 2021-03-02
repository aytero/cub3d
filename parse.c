#include "cub3d.h"

static char	*read_map(int fd, char *tab)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		// check errors
		tab = ft_strjoin(tab, line);
		tab = ft_strjoin(tab, "\n");
	}
	return (tab);
}

void		parse_map(t_all *all, char *file)
{
	int		fd;
	char	*tab;

	tab = NULL;
	if ((fd = open(file, O_RDONLY)) < 0)
	{
	//	error;
	//	free;
		exit(0);
	}
	tab = read_map(fd, tab);
	all->map = ft_split(tab, '\n');
/*
	char	*p1;
	char	**p2;
	p2 = data->map;
	while (*p2)
	{
		p1 = *p2;
		while (*p1)
		{
			printf("%c", *p1);
			p1++;
		}
		printf("\n");
		p2++;
	}
	*/
	close(fd);
	free(tab);
}
