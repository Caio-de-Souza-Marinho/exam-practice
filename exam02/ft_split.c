/*
Assignment name  : ft_split
Expected files   : ft_split.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write a function that takes a string, splits it into words, and returns them as
a NULL-terminated array of strings.

A "word" is defined as a part of a string delimited either by spaces/tabs/new
lines, or by the start/end of the string.

Your function must be declared as follows:

char    **ft_split(char *str);
*/

#include <stdio.h>


#include <stdlib.h>

char    **ft_split(char *str);
int	count_words(char *str);
void	fill_words(char **str_array, char *str);
char	*word_dupe(char *str);
int	ft_wordlen(char *str);

int	main(void)
{
	char *str = "caralho, que bucetao kkkkkkk   .f oda..";
	char **str_arr = ft_split(str);
	for (int i = 0; i < 5; i++)
		printf("%s\n", str_arr[i]);
}

char    **ft_split(char *str)
{
	int num_words = count_words(str);
	char **str_array = malloc((num_words + 1) * sizeof(char *));

	str_array[num_words] = 0;
	fill_words(str_array, str);

	return (str_array);
}

int	count_words(char *str)
{
	int num_words = 0;
	int i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		num_words++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
	}
	return (num_words);
}

void	fill_words(char **str_array, char *str)
{
	int word_index = 0;
	int i = 0;

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		str_array[word_index] = word_dupe(str + i);
		word_index++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
	}
}

char	*word_dupe(char *str)
{
	int i = 0;
	int len = ft_wordlen(str);
	char *word = malloc((len + 1) * sizeof(char));
	
	word[len] = '\0';
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}

int	ft_wordlen(char *str)
{
	int i = 0;

	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	return (i);
}
