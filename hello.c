/*
Assignment name  : hello
Expected files   : hello.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that displays "Hello World!" followed by a \n.

Example:

$>./hello
Hello World!
$>./hello | cat -e
Hello World!$
$>
*/

#include <unistd.h>

void	hello();

int	main(void)
{
	hello();
	return (0);
}

void	hello()
{
	int i = 0;
	char *str = "Hello World!\n";
	while (str[i])
		i++;
	write(1, str, i);	
}
