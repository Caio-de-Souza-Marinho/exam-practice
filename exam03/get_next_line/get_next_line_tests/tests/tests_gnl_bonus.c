#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include "minunit.h"
#include "../src/get_next_line_bonus.h"

MU_TEST(test_gnl_bonus_normal_file)
{
	// ARRANGE
	int	fd = open("test_files/test1.txt", O_RDONLY);
	mu_check(fd != -1);

	const char	*expected_lines[] = 	
		{
			"Hello_Dolly.\n",
			"Goodbye.\n",
			"Hello_Dolly.\n",
			NULL,
		};

	// ACT
	for (int i = 0; expected_lines[i] != NULL; i++)
	{
		char	*actual_result = get_next_line(fd);

		// ASSERT
		mu_assert_string_eq(expected_lines[i], actual_result);

		// FREE MEMORY
		free(actual_result);
	}
	// CLEANUP
	close(fd);
}

MU_TEST(test_gnl_bonus_empty_file)
{
	// ARRANGE
	int	fd = open("test_files/empty.txt", O_RDONLY);
	mu_check(fd != -1);

	// ACT
	char	*actual_result = get_next_line(fd);

	// ASSERT
	mu_assert_string_eq(actual_result, NULL); 

	// CLEANUP
	free(actual_result);
	close(fd);
}

MU_TEST(test_gnl_bonus_single_line_no_newline_file)
{
	// ARRANGE
	int	fd = open("test_files/single_line_no_newline.txt", O_RDONLY);
	mu_check(fd != -1);

	const char	*expected_result = "Single line without newline";

	// ACT
	char	*actual_result = get_next_line(fd);

	// ASSERT
	mu_assert_string_eq(expected_result, actual_result); 
	free(actual_result);

	// Verify that the next call returns NULL
	actual_result = get_next_line(fd);
	mu_assert_string_eq(actual_result, NULL); 

	// CLEANUP
	free(actual_result);
	close(fd);
}

MU_TEST(test_gnl_bonus_large_file)
{
	// ARRANGE
	int	fd = open("test_files/large_file.txt", O_RDONLY);
	mu_check(fd != -1);

	const char	*expected_result = "txtpWDSdOZHx0ZkiGxuBDbAhLhXM5NfZ2U33r4winE79haoilH5MTdfC9TV2xxBLWQmaxwrtsAHl5lIZXyNCNrz33FqdGgz9d988rbm5QURjCQ4FLUffOW7T1JGRdy6uDK1JjjMsbV13TYyk8LRl9CKfHXVVJBn3XejRlbGKGZOgwc3eL1k2Maexjj2Px1Ygu5dlaSXyXOE3S1P5r2Mvpw4LQwnl86R8WUsShWWO9VSRvbPRN5YWJ2uZJdwZcKMYSybGBTkLjVRv7TmvHFKbzJWEQu7x6bM7y4GgqtqtC3gy7cYevzSjqrpQzJJZpYQsNLR3UfMf3btDhhcC3lrSfuUcXLc1eBPzh2r1JUdxqK3YSoeb67UrgI48D313J2swmiBSzkCk1KpweArlrGB7jwsPTAAbj8ZKVrfcy5CkR6E9YTgkK0J3hoaVIDUQ7svaYLr3yYbMOSKIVFuKUwFri3fLSvDrpvmJjBxkmYgZdcM3e5nbBOpkWxPlNQzIFW11EYVb9Sitd9w1mzFodrePbY9Ye4tQwBCKvGlcOFuacdvoOVzM779cfvv2xTRNyUSuncg9LfO4ClG6gR0ix1jWYNhnJD7QuBc96cGhv6Lnij8htoH1wyqkaizTwbYuPiN1nxkiEeZiEUHkvs6VyKbKxe33YhxLhpZFk73KKE8vEg3sQX0DhvO9WE7IyzIIkBh8WUbPlvTtLJ2ssk5Srmdzc47EzemtHO7YkKCrMAjGx9eq8hSlTBhWMvXg8ckoFq3A3aEbiJ436MtzS8dSIE0rWZi4CUyUzKYZNWe8VHSea5Y7xmEVqWicTEdfavJUPEWdxFSOoIrWMXHgDg2tM3EwukYi3t7gTs6cSkpIx1BgDH2ATOrEYVMIe1tYt6UpLb5G0Nduy780EHYiHxMIF1RqfTy5cudhMx1ZJ8hqfJORmrJRujr6uwDxAm9sVtgVET5K70wElRUbHbWCWDVZxHLsssiBqddauLWSoqSyhVOS\n";

	// ACT
	for (int i = 0; i < 100; i++)
	{
		char	*actual_result = get_next_line(fd);

		// ASSERT
		mu_assert_string_eq(expected_result, actual_result);
		free(actual_result);
	}
	// CLEANUP
	close(fd);
}

MU_TEST(test_gnl_bonus_multiple_newlines_file)
{
	// ARRANGE
	int	fd = open("test_files/multiple_newlines.txt", O_RDONLY);
	mu_check(fd != -1);

	const char	*expected_result = "\n";

	// ACT
	for (int i = 0; i < 5; i++)
	{
		char	*actual_result = get_next_line(fd);

		// ASSERT
		mu_assert_string_eq(expected_result, actual_result);
		free(actual_result);
	}

	// Verify that the next call returns NULL (end of file)
	char	*actual_result = get_next_line(fd);
	mu_assert_string_eq(actual_result, NULL);

	// CLEANUP
	free(actual_result);
	close(fd);
}

MU_TEST(test_gnl_bonus_invalid_fd)
{
	// ARRANGE
	int	invalid_fd = -1;

	// ACT
	char	*actual_result = get_next_line(invalid_fd);

	// ASSERT
	mu_assert_string_eq(actual_result, NULL);

	// CLEANUP
	free(actual_result);
}

MU_TEST(test_gnl_bonus_multiple_fds)
{
	// ARRANGE
	int	fd1 = open("test_files/test1.txt", O_RDONLY);
	int	fd2 = open("test_files/test2.txt", O_RDONLY);
	int	fd3 = open("test_files/test3.txt", O_RDONLY);
	mu_check(fd1 != -1 && fd2 != -1 && fd3 != -1);

	const char	*expected_lines_fd1[] = { "Hello_Dolly.\n", "Goodbye.\n", "Hello_Dolly.\n", NULL };
	const char	*expected_lines_fd2[] = { "Ola mundo!\n", "Blz?\n", NULL };
	const char	*expected_lines_fd3[] = { "aaaaaaaa\n", "a\n", "aa\n", "aa\n", "aa\n", "aa\n", NULL };

	int i1 = 0, i2 = 0, i3 = 0;
	int finished1 = 0, finished2 = 0, finished3 = 0;

	while (!finished1 || !finished2 || !finished3)
	{
		// Reading from fd1
		if (!finished1)
		{
			char *actual_result1 = get_next_line(fd1);
			if (actual_result1 == NULL)
			{
				finished1 = 1;
			}
			else
			{
				mu_assert_string_eq(expected_lines_fd1[i1], actual_result1);
				free(actual_result1);
				i1++;
			}
		}

		// Reading from fd2
		if (!finished2)
		{
			char *actual_result2 = get_next_line(fd2);
			if (actual_result2 == NULL)
			{
				finished2 = 1;
			}
			else
			{
				mu_assert_string_eq(expected_lines_fd2[i2], actual_result2);
				free(actual_result2);
				i2++;
			}
		}

		// Reading from fd3
		if (!finished3)
		{
			char *actual_result3 = get_next_line(fd3);
			if (actual_result3 == NULL)
			{
				finished3 = 1;
			}
			else
			{
				mu_assert_string_eq(expected_lines_fd3[i3], actual_result3);
				free(actual_result3);
				i3++;
			}
		}

		// Safety check: Break the loop if all files reach their expected end
		if (finished1 && finished2 && finished3)
			break;
	}

	// CLEANUP
	close(fd1);
	close(fd2);
	close(fd3);
}

MU_TEST(test_gnl_bonus_interleaved_reads_multiple_fds)
{
	// ARRANGE
	int	fd1 = open("test_files/test1.txt", O_RDONLY);
	int	fd2 = open("test_files/test2.txt", O_RDONLY);
	int	fd3 = open("test_files/test3.txt", O_RDONLY);
	mu_check(fd1 != -1 && fd2 != -1 && fd3 != -1);

	const char	*expected_lines_fd1[] = { "Hello_Dolly.\n", "Goodbye.\n", "Hello_Dolly.\n", NULL };
	const char	*expected_lines_fd2[] = { "Ola mundo!\n", "Blz?\n", NULL };
	const char	*expected_lines_fd3[] = { "aaaaaaaa\n", "a\n", "aa\n", "aa\n", "aa\n", "aa\n", NULL };

	// ACT & ASSERT - Interleaved reads from multiple file descriptors
	char	*actual_result1;
	char	*actual_result2;
	char	*actual_result3;

	int	i1 = 0, i2 = 0, i3 = 0;

	// Interleave reading between all 3 file descriptors
	while ((expected_lines_fd1[i1] != NULL || expected_lines_fd2[i2] != NULL || expected_lines_fd3[i3] != NULL))
	{
		if (expected_lines_fd1[i1] != NULL)
		{
			actual_result1 = get_next_line(fd1);
			if (actual_result1)
			{
				mu_assert_string_eq(expected_lines_fd1[i1], actual_result1);
				free(actual_result1);
				i1++;
			}
		}

		if (expected_lines_fd2[i2] != NULL)
		{
			actual_result2 = get_next_line(fd2);
			if (actual_result2)
			{
				mu_assert_string_eq(expected_lines_fd2[i2], actual_result2);
				free(actual_result2);
				i2++;
			}
		}

		if (expected_lines_fd3[i3] != NULL)
		{
			actual_result3 = get_next_line(fd3);
			if (actual_result3)
			{
				mu_assert_string_eq(expected_lines_fd3[i3], actual_result3);
				free(actual_result3);
				i3++;
			}
		}
	}

	// Ensure that all file descriptors reach EOF (NULL)
	mu_check(get_next_line(fd1) == NULL);
	mu_check(get_next_line(fd2) == NULL);
	mu_check(get_next_line(fd3) == NULL);

	// CLEANUP
	close(fd1);
	close(fd2);
	close(fd3);
}

MU_TEST(test_gnl_bonus_closing_and_reopening)
{
	// ARRANGE
	int	fd1 = open("test_files/test1.txt", O_RDONLY);
	mu_check(fd1 != -1);

	const char	*expected_fd1[] = { "Hello_Dolly.\n", "Goodbye.\n", "Hello_Dolly.\n", NULL };

	// ACT & ASSERT - First read
	for (int i = 0; expected_fd1[i] != NULL; i++)
	{
		char *line = get_next_line(fd1);
		mu_assert_string_eq(expected_fd1[i], line);
		free(line);
	}
	// Ensure EOF is reached
	mu_check(get_next_line(fd1) == NULL);

	// Close and reopen the FD to reset
	close(fd1);
	fd1 = open("test_files/test1.txt", O_RDONLY);
	mu_check(fd1 != -1);

	// Read again and check if it starts from the beginning
	for (int i = 0; expected_fd1[i] != NULL; i++)
	{
		char *line = get_next_line(fd1);
		mu_assert_string_eq(expected_fd1[i], line);
		free(line);
	}

	// Ensure EOF is reached
	mu_check(get_next_line(fd1) == NULL);

	// CLEANUP
	close(fd1);
}

MU_TEST_SUITE(get_next_line_bonus_test_suite)
{
	MU_RUN_TEST(test_gnl_bonus_normal_file);
	MU_RUN_TEST(test_gnl_bonus_empty_file);
	MU_RUN_TEST(test_gnl_bonus_single_line_no_newline_file);
	MU_RUN_TEST(test_gnl_bonus_large_file);
	MU_RUN_TEST(test_gnl_bonus_multiple_newlines_file);
	MU_RUN_TEST(test_gnl_bonus_invalid_fd);
	MU_RUN_TEST(test_gnl_bonus_multiple_fds);
	MU_RUN_TEST(test_gnl_bonus_interleaved_reads_multiple_fds);
	MU_RUN_TEST(test_gnl_bonus_closing_and_reopening);
}

int	main(void)
{
	MU_RUN_SUITE(get_next_line_bonus_test_suite);

	MU_REPORT();
	return MU_EXIT_CODE;
}
