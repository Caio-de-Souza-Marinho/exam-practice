#include "bsq.h"

int	parse_header(FILE *file, t_map *map)
{
	char	empty;
	char	obstacle;
	char	full;
	int	lines;
	char	newline;

	if (fscanf(file, "%d %c %c %c%c", &lines, &empty, &obstacle, &full, &newline) != 5)
		return (0);
	if (newline != '\n')
		return (0);
	if (lines <= 0)
		return (0);
	if (empty == obstacle || empty == full || obstacle == full)
		return (0);

	map->lines = lines;
	map->empty = empty;
	map->obstacle = obstacle;
	map->full = full;
	return (1);
}
