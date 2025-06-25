/*
Assignment name  : pgcd
Expected files   : pgcd.c
Allowed functions: printf, atoi, malloc, free
--------------------------------------------------------------------------------

Write a program that takes two strings representing two strictly positive
integers that fit in an int.

Display their highest common denominator followed by a newline (It's always a
strictly positive integer).

If the number of parameters is not 2, display a newline.

Examples:

$> ./pgcd 42 10 | cat -e
2$
$> ./pgcd 42 12 | cat -e
6$
$> ./pgcd 14 77 | cat -e
7$
$> ./pgcd 17 3 | cat -e 
1$
$> ./pgcd | cat -e
$
*/

#include <stdlib.h>
#include <stdio.h>

void	pgcd(unsigned int n1, unsigned int n2);

int	main(int argc, char *argv[])
{
	if (argc == 3)
	{
		unsigned int n1 = atoi(argv[1]);
		unsigned int n2 = atoi(argv[2]);
		pgcd(n1, n2);
	}
	printf("\n");
	return (0);
}

void	pgcd(unsigned int n1, unsigned int n2)
{
	int i = 0;
	if (n1 > n2)
		i = n1;
	else if (n1 < n2)
		i = n2;
	while (1)
	{
		if (n1 % i == 0 && n2 % i == 0)
		{
			printf("%d", i);
			return ;
		}
		i--;
	}
}
