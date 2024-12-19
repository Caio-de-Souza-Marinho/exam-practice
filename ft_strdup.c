/*
Assignment name  : ft_strdup
Expected files   : ft_strdup.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Reproduce the behavior of the function strdup (man strdup).

Your function must be declared as follows:

char    *ft_strdup(char *src);
*/

#include <stdio.h>

char    *ft_strdup(char *src);

int	main(void)
{
	char str[] = "stringasldfsda;lfja;lfja;lsdkfja; ljafkljalfajlfaj";
	printf("%s\n", ft_strdup(str));
	return (0);
}

#include <stdlib.h>

char    *ft_strdup(char *src)
{
	int i = 0;
	while (src[i])
		i++;
	char *res = (char *)malloc((i + 1) * sizeof(char));
	res[i] = '\0';
	i = 0;
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}
