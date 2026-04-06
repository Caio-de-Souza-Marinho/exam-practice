#include "bsq.h"

static int	**make_dp(t_map *map);
static void	free_dp(int **dp, int lines);
static int	min3(int a, int b, int c);

void	solve(t_map *map)
{
	int	**dp;
	int	i;
	int	j;
	int	best_size;
	int	best_row;
	int	best_col;

	dp = make_dp(map);
	if (!dp)
		return ;
	best_size = 0;
	best_row = 0;
	best_col = 0;
	i = 0;
	while (i < map->lines)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->grid[i][j] == map->obstacle)
				dp[i][j] = 0;
			else if (i == 0 || j == 0)
				dp[i][j] = 1;
			else
				dp[i][j] = min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
			if (dp[i][j] > best_size)
			{
				best_size = dp[i][j];
				best_row = i;
				best_col = j;
			}
			j++;
		}
		i++;
	}
	free_dp(dp, map->lines);
	if (best_size == 0)
		return ;
	i = best_row - best_size + 1;
	while (i <= best_row)
	{
		j = best_col - best_size + 1;
		while (j <= best_col)
		{
			map->grid[i][j] = map->full;
			j++;
		}
		i++;
	}
}

static int	**make_dp(t_map *map)
{
	int	**dp;
	int	i;

	dp = malloc(sizeof(int *) * map->lines);
	if (!dp)
		return (NULL);
	i = 0;
	while (i < map->lines)
	{
		dp[i] = malloc(sizeof(int) * map->cols);
		if (!dp[i])
		{
			while (--i >= 0)
				free(dp[i]);
			free(dp);
			return (NULL);
		}
		i++;
	}
	return (dp);
}

static void	free_dp(int **dp, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
		free(dp[i++]);
	free(dp);
}

static int	min3(int a, int b, int c)
{
	if (a < b)
		return (a < c ? a : c);
	return (b < c ? b : c);
}
