/*
Assignment name : get_next_line
Expected files : get_next_line.c (42_EXAM can't take .h for now)
Allowed functions: read, free, malloc
--------------------------------------------------------------------------------

Write a function named get_next_line which prototype should be:
char *get_next_line(int fd);

Your function must return a line that has been read from the file descriptor
passed as parameter. What we call a "line that has been read" is a succession
of 0 to n characters that end with '\n' (ascii code 0x0a) or with
End Of File (EOF).

The line should be returned including the '\n' in case there is one at the end
of the line that has been read. When you've reached the EOF, you must store the
current buffer in a char * and return it. If the buffer is empty you must
return NULL.

In case of error return NULL. In case of not returning NULL, the pointer
should be free-able. Your program will be compiled with the flag
-D BUFFER_SIZE=xx, which has to be used as the buffer size for the read calls
in your functions.

Your function must be memory leak free. When you've reached the EOF, your
function should keep 0 memory allocated with malloc, except the line that
has been returned.

Calling your function get_next_line() in a loop will therefore allow you to
read the text available on a file descriptor one line at a time until the end
of the text, no matter the size of either the text or one of its lines.

Make sure that your function behaves well when it reads from a file, from the
standard output, from a redirection, etc...

No call to another function will be done on the file descriptor between 2
calls of get_next_line(). Finally we consider that get_next_line() has an
undefined behaviour when reading from a binary file.
*/

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

#include <stdio.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);
int	ft_strchr(char *line);
int	ft_strlen(char *str);
char	*ft_strjoin(char *remains, char *buffer);
char	*push_line(char *remains);
char	*cut_next_line(char *remains);

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("test1.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	char		buffer[BUFFER_SIZE + 1];
	buffer[0] = '\0';
	char		*line;
	static char*	remains;
	int		count;

	count = 1;
	while(!ft_strchr(buffer) && count != 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
			return (NULL);
		buffer[count] = '\0';
		remains = ft_strjoin(remains, buffer);
	}
	line = push_line(remains);
	remains = cut_next_line(remains);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}

	return (line);
}

int	ft_strchr(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *remains, char *buffer)
{
	int	i;
	int	j;
	int	size;
	char	*array;

	if (!remains && !buffer)
		return (NULL);
	i = 0;
	j = 0;
	size = ft_strlen(remains) + ft_strlen(buffer);
	array = (char *)malloc(sizeof(char *) * (size + 1));	
	if (!array)
		return (NULL);
	if (remains)
	{
		while(remains[i])
			array[j++] = remains[i++];
		i = 0;
	}
	while (buffer[i])
		array[j++] = buffer[i++];
	array[size] = '\0';
	free(remains);
	return (array);
}

char	*push_line(char *remains)
{
	int	i;
	char	*array;

	i = 0;
	while (remains[i] && remains[i] != '\n')
		i++;
	if (remains[i] == '\n')
		i++;
	array = (char *)malloc(sizeof(char *) * (i + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (remains[i] && remains[i] != '\n')
	{
		array[i] = remains[i];
		i++;
	}
	if (remains[i] == '\n')
	{
		array[i] = '\n';
		array[i + 1] = '\0';
		return (array);
	}
	array[i] = '\0';
	return (array);
}

char	*cut_next_line(char *remains)
{
	int	i;
	int	j;
	char	*array;

	i = 0;
	j = 0;
	while (remains[i] && remains[i] != '\n')
		i++;
	if (!remains[i])
	{
		free(remains);
		return (NULL);
	}
	array = (char *)malloc(sizeof(char *) * (ft_strlen(remains) - i + 1));
	if (!array)
		return (NULL);
	i++;
	while (remains[i])
	{
		array[j] = remains[i];
		i++;
		j++;
	}
	array[j] = '\0';
	free(remains);
	return (array);
}
