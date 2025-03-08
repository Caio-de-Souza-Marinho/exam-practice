#include "minunit.h"
#include "../src/ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

MU_TEST(test_ft_printf_print_one_number_x_specifier)
{
	// ARRANGE
	unsigned int	num = 42;
	char		expected_output[] = "2a";
	int		expected_return_value = 2;  // Expected number of characters printed
	char		buffer[100];
	int		temp_fd;
	int		saved_stdout;

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
	int	actual_return_value = ft_printf("%x", num);

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

MU_TEST(test_ft_printf_print_one_number_X_specifier)
{
	// ARRANGE
	unsigned int	num = 42;
	char		expected_output[] = "2A";
	int		expected_return_value = 2;  // Expected number of characters printed
	char		buffer[100];
	int		temp_fd;
	int		saved_stdout;

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
	int	actual_return_value = ft_printf("%X", num);

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

MU_TEST(test_ft_printf_one_positive_hex_with_width_and_precision)
{
	// ARRANGE
	unsigned int num = 42;
	char expected_output[] = "     0002a";
	int expected_return_value = 10;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%10.5x", num);

	// Reset stdout and read output
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	close(temp_fd);

	FILE *temp_file = fopen("/tmp/test_output.txt", "r");
	if (!temp_file)
		mu_fail("Failed to open temporary file");
	size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, temp_file);
	buffer[bytes_read] = '\0';
	fclose(temp_file);

	// ASSERT
	mu_assert_string_eq(expected_output, buffer);
	mu_assert_int_eq(expected_return_value, actual_return_value);

	// Clean up
	remove("/tmp/test_output.txt");
}

MU_TEST(test_ft_printf_one_positive_hex_with_large_width)
{
	// ARRANGE
	unsigned int num = 255;
	char expected_output[] = "                                                ff";
	int expected_return_value = 50;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%50x", num);

	// Reset stdout and read output
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	close(temp_fd);

	FILE *temp_file = fopen("/tmp/test_output.txt", "r");
	if (!temp_file)
		mu_fail("Failed to open temporary file");
	size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, temp_file);
	buffer[bytes_read] = '\0';
	fclose(temp_file);

	// ASSERT
	mu_assert_string_eq(expected_output, buffer);
	mu_assert_int_eq(expected_return_value, actual_return_value);

	// Clean up
	remove("/tmp/test_output.txt");
}

MU_TEST(test_ft_printf_zero_hex_with_width_and_precision)
{
	// ARRANGE
	unsigned int num = 0;
	char expected_output[] = "     00000";
	int expected_return_value = 10;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%10.5x", num);

	// Reset stdout and read output
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	close(temp_fd);

	FILE *temp_file = fopen("/tmp/test_output.txt", "r");
	if (!temp_file)
		mu_fail("Failed to open temporary file");
	size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, temp_file);
	buffer[bytes_read] = '\0';
	fclose(temp_file);

	// ASSERT
	mu_assert_string_eq(expected_output, buffer);
	mu_assert_int_eq(expected_return_value, actual_return_value);

	// Clean up
	remove("/tmp/test_output.txt");
}

MU_TEST(test_ft_printf_one_positive_hex_upper_with_width_and_precision)
{
	// ARRANGE
	unsigned int num = 42;
	char expected_output[] = "     0002A";
	int expected_return_value = 10;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%10.5X", num);

	// Reset stdout and read output
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	close(temp_fd);

	FILE *temp_file = fopen("/tmp/test_output.txt", "r");
	if (!temp_file)
		mu_fail("Failed to open temporary file");
	size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, temp_file);
	buffer[bytes_read] = '\0';
	fclose(temp_file);

	// ASSERT
	mu_assert_string_eq(expected_output, buffer);
	mu_assert_int_eq(expected_return_value, actual_return_value);

	// Clean up
	remove("/tmp/test_output.txt");
}

MU_TEST(test_ft_printf_one_positive_hex_upper_with_large_width)
{
	// ARRANGE
	unsigned int num = 255;
	char expected_output[] = "                                                FF";
	int expected_return_value = 50;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%50X", num);

	// Reset stdout and read output
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	close(temp_fd);

	FILE *temp_file = fopen("/tmp/test_output.txt", "r");
	if (!temp_file)
		mu_fail("Failed to open temporary file");
	size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, temp_file);
	buffer[bytes_read] = '\0';
	fclose(temp_file);

	// ASSERT
	mu_assert_string_eq(expected_output, buffer);
	mu_assert_int_eq(expected_return_value, actual_return_value);

	// Clean up
	remove("/tmp/test_output.txt");
}

MU_TEST(test_ft_printf_zero_hex_upper_with_width_and_precision)
{
	// ARRANGE
	unsigned int num = 0;
	char expected_output[] = "     00000";
	int expected_return_value = 10;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%10.5X", num);

	// Reset stdout and read output
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	close(temp_fd);

	FILE *temp_file = fopen("/tmp/test_output.txt", "r");
	if (!temp_file)
		mu_fail("Failed to open temporary file");
	size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, temp_file);
	buffer[bytes_read] = '\0';
	fclose(temp_file);

	// ASSERT
	mu_assert_string_eq(expected_output, buffer);
	mu_assert_int_eq(expected_return_value, actual_return_value);

	// Clean up
	remove("/tmp/test_output.txt");
}

MU_TEST_SUITE(ft_printf_x_and_X_test_suite)
{

	MU_RUN_TEST(test_ft_printf_print_one_number_x_specifier);
	MU_RUN_TEST(test_ft_printf_print_one_number_X_specifier);
	MU_RUN_TEST(test_ft_printf_one_positive_hex_with_width_and_precision);
	MU_RUN_TEST(test_ft_printf_one_positive_hex_with_large_width);
	MU_RUN_TEST(test_ft_printf_zero_hex_with_width_and_precision);
	MU_RUN_TEST(test_ft_printf_one_positive_hex_upper_with_width_and_precision);
	MU_RUN_TEST(test_ft_printf_one_positive_hex_upper_with_large_width);
	MU_RUN_TEST(test_ft_printf_zero_hex_upper_with_width_and_precision);
}
