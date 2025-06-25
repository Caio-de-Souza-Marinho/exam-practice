#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "src/get_next_line.h"

int	main(void)
{
	int	fd1 = open("tests/test_files/test1.txt", O_RDONLY);
	int	fd2 = open("tests/test_files/test2.txt", O_RDONLY);
	int	fdi = 3;
	int	i = 0;
	char	*line;

	printf("fd1 = %d\n", fd1);
	printf("fd2 = %d\n", fd2);

	printf("START OF FILE %d\n", fdi);
	while ((line = get_next_line(fd1)) != NULL )
	{
		printf("Line %d >>> %s", i++, line);
		free(line);
	}
	printf("END OF FILE %d\n", fdi++);
	close(fd1);
	i = 0;
	
	printf("START OF FILE %d\n", fdi);
	while ((line = get_next_line(fd2)) != NULL )
	{
		printf("Line %d >>> %s", i++, line);
		free(line);
	}
	printf("END OF FILE %d\n", fdi++);
	close(fd2);
	i = 0;

	return (0);
}
