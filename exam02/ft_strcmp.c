/*
Assignment name  : ft_strcmp
Expected files   : ft_strcmp.c
Allowed functions:
--------------------------------------------------------------------------------

Reproduce the behavior of the function strcmp (man strcmp).

Your function must be declared as follows:

int    ft_strcmp(char *s1, char *s2);
*/

#include <stdio.h>

int    ft_strcmp(char *s1, char *s2);

int	main(void)
{
	char *s1 = "caio";
	char *s2 = "caio";
	char *s3 = "cbio";
	char *s4 = "caho";
	int res1 = ft_strcmp(s1, s2);
	printf("%d\n", res1);
	int res2 = ft_strcmp(s1, s3);
	printf("%d\n", res2);
	int res3 = ft_strcmp(s1, s4);
	printf("%d\n", res3);
}

int    ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
