#include "bsq.h"

static void	process_map(FILE *file);

int	main(int argc, char **argv)
{
	FILE	*file;

	if (argc == 1)
	{
		process_map(stdin);
		return (0);
	}

	for (int i = 1; i < argc; i++)
	{
		file = fopen(argv[i], "r");
		if (!file)
			fprintf(stderr, "map error\n");
		else
      		{
			process_map(file);
			fclose(file);
		}
		if (i < argc - 1)
			fprintf(stdout, "\n");
	}

	return (0);
}

static void	process_map(FILE *file)
{
	t_map	map = {0};

	if (!parse_header(file, &map) || !read_map(file, &map))
	{
		fprintf(stderr, "map error\n");
		free_map(&map);
		return ;
	}
	solve(&map);
	print_map(&map);
	free_map(&map);
}
