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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_itoa(int nbr);
int	count_digits(int nbr);

int	main(void)
{
	//int num = -4232;
	printf("%s\n", ft_itoa(INT_MAX));
	return (0);
}

char	*ft_itoa(int nbr)
{
	int len = count_digits(nbr);
	char *str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	int i = 0;
	long num = nbr;

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
	i = len - 1;
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
	int len = 0;

	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	if (nbr == 0)
	{
		len++;
		return (len);
	}
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}
