#include "minunit.h"
#include "../src/ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

MU_TEST(test_ft_printf_one_int)
{
	// ARRANGE
	int	num = 0;
	char	expected_output[] = "0";
	int	expected_return_value = 1;  // Expected number of characters printed
	char	buffer[100];
	int	temp_fd;
	int	saved_stdout;

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
	int	actual_return_value = ft_printf("%d", num);

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

MU_TEST(test_ft_printf_one_positive_int_and_one_normal)
{
	// ARRANGE
	int	num1 = 42;
	int	num2 = -42;
	char	expected_output[] = "42-42";
	int	expected_return_value = 5;  // Expected number of characters printed
	char	buffer[100];
	int	temp_fd;
	int	saved_stdout;

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
	int	actual_return_value = ft_printf("%d%d", num1, num2);

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

MU_TEST(test_ft_printf_int_max)
{
	// ARRANGE
	int	num = INT_MAX;
	char	expected_output[] = "2147483647";
	int	expected_return_value = 10;  // Expected number of characters printed
	char	buffer[100];
	int	temp_fd;
	int	saved_stdout;

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
	int	actual_return_value = ft_printf("%d", num);

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

MU_TEST(test_ft_printf_int_min)
{
	// ARRANGE
	int	num = INT_MIN;
	char	expected_output[] = "-2147483648";
	int	expected_return_value = 11;  // Expected number of characters printed
	char	buffer[100];
	int	temp_fd;
	int	saved_stdout;

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
	int	actual_return_value = ft_printf("%d", num);

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

MU_TEST(test_ft_printf_int_max_plus_one)
{
	// ARRANGE
	int	num = INT_MAX;
	char	expected_output[] = "-2147483648";
	int	expected_return_value = 11;  // Expected number of characters printed
	char	buffer[100];
	int	temp_fd;
	int	saved_stdout;

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
	int	actual_return_value = ft_printf("%d", num + 1);

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

MU_TEST(test_ft_printf_int_min_minus_one)
{
	// ARRANGE
	int	num = INT_MIN;
	char	expected_output[] = "2147483647";
	int	expected_return_value = 10;  // Expected number of characters printed
	char	buffer[100];
	int	temp_fd;
	int	saved_stdout;

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
	int	actual_return_value = ft_printf("%d", num - 1);

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

MU_TEST(test_ft_printf_two_unsigned_int_int_max_and_int_min)
{
	// ARRANGE
	unsigned int	num1 = INT_MIN;
	unsigned int	num2 = INT_MAX;
	char		expected_output[] = "21474836482147483647";
	int		expected_return_value = 20;  // Expected number of characters printed
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
	int	actual_return_value = ft_printf("%u%u", num1, num2);

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

MU_TEST(test_ft_printf_one_positive_int_with_width)
{
	// ARRANGE
	int num = 42;
	char expected_output[] = "     42"; // Width of 7
	int expected_return_value = 7;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%7d", num);

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

MU_TEST(test_ft_printf_one_negative_int_with_width)
{
	// ARRANGE
	int num = -42;
	char expected_output[] = "    -42"; // Width of 7
	int expected_return_value = 7;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%7d", num);

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

MU_TEST(test_ft_printf_one_int_left_aligned)
{
	// ARRANGE
	int num = 42;
	char expected_output[] = "42     "; // Width of 7, left-aligned
	int expected_return_value = 7;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%-7d", num);

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

MU_TEST(test_ft_printf_one_positive_int_plus_flag)
{
	// ARRANGE
	int num = 42;
	char expected_output[] = "+42";
	int expected_return_value = 3;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%+d", num);

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

MU_TEST(test_ft_printf_one_negative_int_plus_flag)
{
	// ARRANGE
	int num = -42;
	char expected_output[] = "-42"; // Plus flag has no effect on negative numbers
	int expected_return_value = 3;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%+d", num);

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

MU_TEST(test_ft_printf_one_positive_int_space_flag)
{
	// ARRANGE
	int num = 42;
	char expected_output[] = " 42"; // Space flag adds a space for positive numbers
	int expected_return_value = 3;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("% d", num);

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

MU_TEST(test_ft_printf_one_positive_int_zero_flag)
{
	// ARRANGE
	int num = 42;
	char expected_output[] = "00042"; // Zero flag pads with zeros
	int expected_return_value = 5;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%05d", num);

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

MU_TEST(test_ft_printf_one_negative_int_zero_flag)
{
	// ARRANGE
	int num = -42;
	char expected_output[] = "-0042"; // Zero flag pads with zeros after the minus sign
	int expected_return_value = 5;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%05d", num);

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

MU_TEST(test_ft_printf_one_positive_int_with_precision)
{
	// ARRANGE
	int num = 42;
	char expected_output[] = "00042"; // Precision pads with zeros up to 5 digits
	int expected_return_value = 5;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%.5d", num);

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

MU_TEST(test_ft_printf_one_negative_int_with_precision)
{
	// ARRANGE
	int num = -42;
	char expected_output[] = "-00042"; // Precision pads with zeros after the minus sign
	int expected_return_value = 6;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%.5d", num);

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

MU_TEST(test_ft_printf_one_positive_int_with_width_and_precision)
{
	// ARRANGE
	int num = 42;
	char expected_output[] = "     00042";
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
	int actual_return_value = ft_printf("%10.5d", num);

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

MU_TEST(test_ft_printf_one_negative_int_with_width_and_precision)
{
	// ARRANGE
	int num = -42;
	char expected_output[] = "    -00042";
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
	int actual_return_value = ft_printf("%10.5d", num);

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

MU_TEST(test_ft_printf_one_positive_int_with_large_width)
{
	// ARRANGE
	int num = 42;
	char expected_output[] = "                                                42";
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
	int actual_return_value = ft_printf("%50d", num);

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

MU_TEST(test_ft_printf_one_negative_int_with_large_width)
{
	// ARRANGE
	int num = -42;
	char expected_output[] = "                                               -42";
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
	int actual_return_value = ft_printf("%50d", num);

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

MU_TEST(test_ft_printf_one_int_zero_flag_and_left_alignment)
{
	// ARRANGE
	int num = 42;
	char expected_output[] = "42        ";
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
	int actual_return_value = ft_printf("%-10d", num);

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

MU_TEST(test_ft_printf_zero)
{
	// ARRANGE
	int num = 0;
	char expected_output[] = "0";
	int expected_return_value = 1;
	char buffer[100];
	int temp_fd, saved_stdout;

	// Save stdout
	saved_stdout = dup(STDOUT_FILENO);

	// Redirect stdout
	temp_fd = open("/tmp/test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1 || dup2(temp_fd, STDOUT_FILENO) == -1)
		mu_fail("Failed to set up test output");

	// ACT
	int actual_return_value = ft_printf("%d", num);

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

MU_TEST(test_ft_printf_zero_with_width_and_precision)
{
	// ARRANGE
	int num = 0;
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
	int actual_return_value = ft_printf("%10.5d", num);

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

MU_TEST_SUITE(ft_printf_d_and_i_test_suite)
{
	MU_RUN_TEST(test_ft_printf_one_int);
	MU_RUN_TEST(test_ft_printf_one_positive_int_and_one_normal);
	MU_RUN_TEST(test_ft_printf_int_max);
	MU_RUN_TEST(test_ft_printf_int_min);
	MU_RUN_TEST(test_ft_printf_int_max_plus_one);
	MU_RUN_TEST(test_ft_printf_int_min_minus_one);
	MU_RUN_TEST(test_ft_printf_int_min_minus_one);
	MU_RUN_TEST(test_ft_printf_two_unsigned_int_int_max_and_int_min);
	MU_RUN_TEST(test_ft_printf_one_positive_int_with_width);
	MU_RUN_TEST(test_ft_printf_one_negative_int_with_width);
	MU_RUN_TEST(test_ft_printf_one_int_left_aligned);
	MU_RUN_TEST(test_ft_printf_one_positive_int_plus_flag);
	MU_RUN_TEST(test_ft_printf_one_negative_int_plus_flag);
	MU_RUN_TEST(test_ft_printf_one_positive_int_space_flag);
	MU_RUN_TEST(test_ft_printf_one_positive_int_zero_flag);
	MU_RUN_TEST(test_ft_printf_one_negative_int_zero_flag);
	MU_RUN_TEST(test_ft_printf_one_positive_int_with_precision);
	MU_RUN_TEST(test_ft_printf_one_negative_int_with_precision);
	MU_RUN_TEST(test_ft_printf_one_positive_int_with_width_and_precision);
	MU_RUN_TEST(test_ft_printf_one_negative_int_with_width_and_precision);
	MU_RUN_TEST(test_ft_printf_one_positive_int_with_large_width);
	MU_RUN_TEST(test_ft_printf_one_negative_int_with_large_width);
	MU_RUN_TEST(test_ft_printf_one_int_zero_flag_and_left_alignment);
	MU_RUN_TEST(test_ft_printf_zero);
	MU_RUN_TEST(test_ft_printf_zero_with_width_and_precision);
}
