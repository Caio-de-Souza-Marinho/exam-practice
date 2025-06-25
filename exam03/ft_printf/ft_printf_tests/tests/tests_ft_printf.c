#include "minunit.h"
#include "../src/ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#include "tests_ft_printf_c_and_%.c"
#include "tests_ft_printf_s.c"
#include "tests_ft_printf_p.c"
#include "tests_ft_printf_d_and_i.c"
#include "tests_ft_printf_u.c"
#include "tests_ft_printf_x_and_X.c"

MU_TEST(test_ft_printf_print_mix)
{
	// ARRANGE
	char		c = 'a';
	char		*str = "caio";
	char		*ptr = (void *)0x1234abcd; // Example pointer to test
	int		num1 = 42;
	int		num2 = -42;
	unsigned int	num3 = 4200;
	unsigned int	num4 = 42;
	char		expected_output[200];
	int		expected_return_value;  // Expected number of characters printed
	char		buffer[200];
	int		temp_fd;
	int		saved_stdout;

	// Create the expected output using snprintf
	expected_return_value = snprintf(expected_output, sizeof(expected_output), "%c%s%p%%%d%d%u%x%X", c, str, ptr, num1, num2, num3, num4, num4);

	// Save the current stdout file descriptor
	saved_stdout = dup(STDOUT_FILENO);

	// Create a temporary file and get its file descriptor
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1) {
		mu_fail("Failed to open temporary file");
	}

	// Redirect stdout to the temporary file
	if (dup2(temp_fd, STDOUT_FILENO) == -1) {
		mu_fail("Failed to redirect stdout");
	}

	// ACT
	int	actual_return_value = ft_printf("%c%s%p%%%d%d%u%x%X", c, str, ptr, num1, num2, num3, num4, num4);

	// Reset stdout to its original value
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);  // Restore the original stdout
	close(saved_stdout);
	close(temp_fd);

	// Read the content of the temporary file
	FILE	*temp_file = fopen("/tmp/test_output.txt", "r");
	if (!temp_file) {
		mu_fail("Failed to open temporary file for reading");
	}
	size_t	bytes_read = fread(buffer, 1, sizeof(buffer) - 1, temp_file);
	buffer[bytes_read] = '\0';  // Null-terminate the string read
	fclose(temp_file);

	// ASSERT
	mu_assert_string_eq(expected_output, buffer);  // Check printed output
	mu_assert_int_eq(expected_return_value, actual_return_value);  // Check return value

	// Clean up the temporary file
	remove("/tmp/test_output.txt");
}

MU_TEST_SUITE(ft_printf_test_suite)
{
	MU_RUN_TEST(test_ft_printf_print_mix);
}

int	main(void)
{
	MU_RUN_SUITE(ft_printf_test_suite);
	MU_RUN_SUITE(ft_printf_c_and_percent_sign_test_suite);
	MU_RUN_SUITE(ft_printf_s_test_suite);
	MU_RUN_SUITE(ft_printf_p_test_suite);
	MU_RUN_SUITE(ft_printf_d_and_i_test_suite);
	MU_RUN_SUITE(ft_printf_u_test_suite);
	MU_RUN_SUITE(ft_printf_x_and_X_test_suite);

	MU_REPORT();
	return MU_EXIT_CODE;
}
