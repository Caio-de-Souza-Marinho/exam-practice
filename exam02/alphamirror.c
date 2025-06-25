/*
Assignment name  : alpha_mirror
Expected files   : alpha_mirror.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program called alpha_mirror that takes a string and displays this string
after replacing each alphabetical character by the opposite alphabetical
character, followed by a newline.

'a' becomes 'z', 'Z' becomes 'A'
'd' becomes 'w', 'M' becomes 'N'

and so on.

Case is not changed.

If the number of arguments is not 1, display only a newline.

Examples:

$>./alpha_mirror "abc"
zyx
$>./alpha_mirror "My horse is Amazing." | cat -e
Nb slihv rh Znzarmt.$
$>./alpha_mirror | cat -e
$
$>
*/

#include <unistd.h>

int	ft_isupper(char c);
int	ft_islower(char c);

void	alpha_mirror(char *str);

int	main(int argc, char *argv[])
{
	if (argc == 2)
		alpha_mirror(argv[1]);
	write(1, "\n", 1);
	return (0);
}

void	alpha_mirror(char *str)
{
	int i = 0;
	int magic_number1 = 219;
	int magic_number2 = 155;
	while (str[i])
	{
		if (ft_islower(str[i]))
			str[i] = magic_number1 - str[i];
		else if (ft_isupper(str[i]))
			str[i] = magic_number2 - str[i];
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_islower(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int	ft_isupper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}
