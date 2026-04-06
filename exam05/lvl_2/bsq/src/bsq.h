#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_map
{
	char	**grid;
	int	lines;
	int	cols;
	char	empty;
	char	obstacle;
	char	full;
}	t_map;

int	parse_header(FILE *file, t_map *map);
int	read_map(FILE *file, t_map *map);
void	solve(t_map *map);
void	print_map(t_map *map);
void	free_map(t_map *map);

#endif
