#include "bsq.h"

void	print_map(t_map *map)
{
	int	i = 0;

	while (i < map->lines)
	{
		fputs(map->grid[i], stdout);
		fputs("\n", stdout);
		i++;
	}
}
