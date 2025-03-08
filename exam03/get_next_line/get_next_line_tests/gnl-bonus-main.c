#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "src/get_next_line_bonus.h"

int	main(void)
{
	int	fd1 = open("tests/test_files/test1.txt", O_RDONLY);
	int	fd2 = open("tests/test_files/test2.txt", O_RDONLY);
	int	fd3 = open("tests/test_files/test3.txt", O_RDONLY);
	int	fd1i = 1;
	int	fd2i = 1;
	int	fd3i = 1;

	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		perror("Error opening files");
		return (1);
	}

	char	*line1;
	char	*line2;
	char	*line3;
	int	finished1 = 0, finished2 = 0, finished3 = 0;

	while (!finished1 || !finished2 || !finished3)
	{
		if (!finished1 && (line1 = get_next_line(fd1)))
		{
			printf("File 1, Line %d: %s", fd1i++, line1);
			free(line1);
		}
		else finished1 = 1;

		if (!finished2 && (line2 = get_next_line(fd2)))
		{
			printf("File 2, Line %d: %s", fd2i++, line2);
			free(line2);
		}
		else finished2 = 1;

		if (!finished3 && (line3 = get_next_line(fd3)))
		{
			printf("File 3, Line %d: %s", fd3i++, line3);
			free(line3);
		}
		else finished3 = 1;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
