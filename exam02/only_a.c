/*
Assignment name  : only_a
Expected files   : only_a.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that displays a 'a' character on the standard output.
*/

#include <unistd.h>

void	only_a();

int	main(void)
{
	only_a();
	return (0);
}

void	only_a()
{
	write(1, "a", 1);	
}
