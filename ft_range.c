/*
Assignment name  : ft_range
Expected files   : ft_range.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write the following function:

int     *ft_range(int start, int end);

It must allocate (with malloc()) an array of integers, fill it with consecutive
values that begin at start and end at end (Including start and end !), then
return a pointer to the first value of the array.

Examples:

- With (1, 3) you will return an array containing 1, 2 and 3.
- With (-1, 2) you will return an array containing -1, 0, 1 and 2.
- With (0, 0) you will return an array containing 0.
- With (0, -3) you will return an array containing 0, -1, -2 and -3.
*/

#include <stdlib.h>


#include <stdio.h>

int     *ft_range(int start, int end);

int	main(void)
{
	int *range1 = ft_range(1, 3);
	for (int i = 0; i < 3; i++)
		printf("%d ", range1[i]);
	printf("\n");
	int *range2 = ft_range(-1, 2);
	for (int i = 0; i < 4; i++)
		printf("%d ", range2[i]);
	printf("\n");
	int *range3 = ft_range(0, 0);
	for (int i = 0; i < 1; i++)
		printf("%d ", range3[i]);
	printf("\n");
	int *range4 = ft_range(0, -3);
	for (int i = 0; i < 4; i++)
		printf("%d ", range4[i]);
	printf("\n");
	return (0);
}

int     *ft_range(int start, int end)
{
	int diff = 0;
	int *res;
	if (start <= end)
		diff = (end - start) + 1;
	else if (start > end)
		diff = ((-end) - start) + 1;
	res = (int *)malloc(diff * sizeof(int));
	int i = 0;
	while (i < diff)
	{
		if (start <= end)
		{
			res[i] = start;
			i++;
			start++;
		}
		else if (start > end)
		{
			res[i] = start;
			i++;
			start--;
		}
	}
	return (res);
}
