/*
Assignment name  : last_word
Expected files   : last_word.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays its last word followed by a \n.

A word is a section of string delimited by spaces/tabs or by the start/end of
the string.

If the number of parameters is not 1, or there are no words, display a newline.

Example:

$> ./last_word "FOR PONY" | cat -e
PONY$
$> ./last_word "this        ...       is sparta, then again, maybe    not" | cat -e
not$
$> ./last_word "   " | cat -e
$
$> ./last_word "a" "b" | cat -e
$
$> ./last_word "  lorem,ipsum  " | cat -e
lorem,ipsum$
$>
*/

#include <unistd.h>

void	last_word(char *str);

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		char *str = argv[1];
		last_word(str);
		write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	return (0);
}

void	last_word(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	i--;
	while ((str[i] == ' ' || str[i] == '\t') && i != 0)
		i--;
	while (str[i] != ' ' && str[i] != '\t' && i != 0)
		i--;
	if (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		write(1, &str[i], 1);
		i++;
	}
}
