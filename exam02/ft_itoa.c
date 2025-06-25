/*
Assignment name  : ft_itoa
Expected files   : ft_itoa.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write a function that takes an int and converts it to a null-terminated string.
The function returns the result in a char array that you must allocate.

Your function must be declared as follows:

char	*ft_itoa(int nbr);
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char	*ft_itoa(int nbr);
int	count_digits(int nbr);

int	main(void)
{
	//int num = 4232;
	printf("%s\n", ft_itoa(INT_MIN));
	return (0);
}

char	*ft_itoa(int nbr)
{
	int nbr_len = count_digits(nbr);
	char *str = (char *)malloc((nbr_len + 1) * sizeof(char));
	str[nbr_len] = '\0';
	long num = nbr;
	int i = 0;

	if (num < 0)
	{
		str[i] = '-';
		num = -num;
		i++;
	}
	if (num == 0)
	{
		str[i] = '0';
		return (str);
	}
	i = nbr_len - 1;
	while (num != 0)
	{
		str[i] = (num % 10) + 48;
		num /= 10;
		i--;
	}
	return (str);
}

int	count_digits(int nbr)
{
	int count = 0;
	if (nbr < 0)
	{
		count++;
		nbr = -nbr;
	}
	if (nbr == 0)
	{
		count++;
		return (count);
	}
	while (nbr != 0)
	{
		count++;
		nbr /= 10;
	}
	return (count);
}
