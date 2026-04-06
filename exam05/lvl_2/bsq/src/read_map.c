#include "bsq.h"

static int	validate_line(char *line, t_map *map);

int	read_map(FILE *file, t_map *map)
{
	char	*line;
	size_t	buf_size;
	ssize_t	len;
	int	i;

	map->grid = malloc(sizeof(char *) * map->lines);
	if (!map->grid)
		return (0);
	buf_size = 0;
	line = NULL;
	i = 0;
	while (i < map->lines && (len = getline(&line, &buf_size, file)) != -1)
	{
		if (line[len - 1] != '\n')
		{
    			free(line);
			return (0);
		}
		line[--len] = '\0';
		if (i == 0)
		{
			if (len == 0)
				return (0);
			map->cols = (int)len;
		}
		if (!validate_line(line, map))
		{
			free(line);
			return (0);
		}
		map->grid[i] = malloc(sizeof(char) * (len + 1));
		if (!map->grid[i])
		{
			free(line);
			return (0);
		}
		strcpy(map->grid[i], line);
		i++;
	}
	free(line);
	if (i != map->lines)
		return (0);
	return (1);
}

static int	validate_line(char *line, t_map *map)
{
	int	i = 0;

	while (line[i])
	{
		if (line[i] != map->empty && line[i] != map->obstacle)
			return (0);
		i++;
	}
	if (i != map->cols)
		return (0);
	return (1);
}
