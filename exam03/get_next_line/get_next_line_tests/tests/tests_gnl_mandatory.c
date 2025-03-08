#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include "minunit.h"
#include "../src/get_next_line.h"

MU_TEST(test_gnl_mandatory_normal_file)
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

MU_TEST(test_gnl_mandatory_empty_file)
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

MU_TEST(test_gnl_mandatory_single_line_no_newline_file)
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

MU_TEST(test_gnl_mandatory_large_file)
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

MU_TEST(test_gnl_mandatory_multiple_newlines_file)
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

MU_TEST(test_gnl_mandatory_invalid_fd)
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

MU_TEST_SUITE(get_next_line_test_suite)
{
	MU_RUN_TEST(test_gnl_mandatory_normal_file);
	MU_RUN_TEST(test_gnl_mandatory_empty_file);
	MU_RUN_TEST(test_gnl_mandatory_single_line_no_newline_file);
	MU_RUN_TEST(test_gnl_mandatory_large_file);
	MU_RUN_TEST(test_gnl_mandatory_multiple_newlines_file);
	MU_RUN_TEST(test_gnl_mandatory_invalid_fd);
}

int	main(void)
{
	MU_RUN_SUITE(get_next_line_test_suite);

	MU_REPORT();
	return MU_EXIT_CODE;
}
