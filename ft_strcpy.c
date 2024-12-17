/*
Assignment name  : ft_strcpy
Expected files   : ft_strcpy.c
Allowed functions: 
--------------------------------------------------------------------------------

Reproduce the behavior of the function strcpy (man strcpy).

Your function must be declared as follows:

char    *ft_strcpy(char *s1, char *s2);
*/

#include <stdio.h>

char    *ft_strcpy(char *s1, char *s2);

int	main(void)
{
	char s1[4];
	printf("s1 = %s\n", s1);
	char *s2 = "caio";
	printf("s2 = %s\n", s2);
	char *res = ft_strcpy(s1, s2);
	printf("res = %s\n", res);
	return (0);
}

char    *ft_strcpy(char *s1, char *s2)
{
	int i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
