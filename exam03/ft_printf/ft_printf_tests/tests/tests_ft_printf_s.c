#include "minunit.h"
#include "../src/ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

MU_TEST(test_ft_printf_one_string)
{
	// ARRANGE
	char	*s = "caio";
	char	expected_output[] = "caio";
	int	expected_return_value = 4;  // Expected number of characters printed
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
	int	actual_return_value = ft_printf("%s", s);

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

MU_TEST(test_ft_printf_two_strings)
{
	// ARRANGE
	char	*s1 = "caio";
	char	*s2 = "oiac";
	char	expected_output[] = "caiooiac";
	int	expected_return_value = 8;  // Expected number of characters printed
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
	int	actual_return_value = ft_printf("%s%s", s1, s2);

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

MU_TEST(test_ft_printf_str_flag_null_pointer)
{
	// ARRANGE
	char	*s = NULL;
	char	expected_output[] = "(null)";
	int	expected_return_value = 6;  // Expected number of characters printed
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
	int	actual_return_value = ft_printf("%s", s);

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

MU_TEST(test_ft_printf_str_with_width_of_10)
{
	// ARRANGE
	char	*s = "caio";
	char	expected_output[] = "      caio";
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
	int	actual_return_value = ft_printf("%10s", s);

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

MU_TEST(test_ft_printf_str_with_width_and_left_aligned)
{
	// ARRANGE
	char	*s = "caio";
	char	expected_output[] = "caio      ";
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
	int	actual_return_value = ft_printf("%-10s", s);

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

MU_TEST(test_ft_printf_str_with_precision)
{
	// ARRANGE
	char	*s = "caio";
	char	expected_output[] = "ca";
	int	expected_return_value = 2;  // Expected number of characters printed
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
	int	actual_return_value = ft_printf("%.2s", s);

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

MU_TEST(test_ft_printf_str_with_width_and_precision)
{
	// ARRANGE
	char	*s = "caio";
	char	expected_output[] = "        ca";
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
	int	actual_return_value = ft_printf("%10.2s", s);

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

MU_TEST(test_ft_printf_str_with_width_and_precision_and_left_aligned)
{
	// ARRANGE
	char	*s = "caio";
	char	expected_output[] = "ca        ";
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
	int	actual_return_value = ft_printf("%-10.2s", s);

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

MU_TEST(test_ft_printf_str_empty_string)
{
	// ARRANGE
	char	*s = "";
	char	expected_output[] = "";
	int	expected_return_value = 0;  // Expected number of characters printed
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
	int	actual_return_value = ft_printf("%s", s);

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

MU_TEST(test_ft_printf_str_width_smaller_than_string_length)
{
	// ARRANGE
	char	*s = "caio";
	char	expected_output[] = "caio";
	int	expected_return_value = 4;  // Expected number of characters printed
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
	int	actual_return_value = ft_printf("%1s", s);

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

MU_TEST(test_ft_printf_str_precision_greater_than_string_length)
{
	// ARRANGE
	char	*s = "caio";
	char	expected_output[] = "caio";
	int	expected_return_value = 4;  // Expected number of characters printed
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
	int	actual_return_value = ft_printf("%.5s", s);

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

MU_TEST(test_ft_printf_str_large_width)
{
	// ARRANGE
	char	*s = "Hello";
	char	expected_output[] = "                                                                                               Hello";
	int	expected_return_value = 100;  // Expected number of characters printed
	char	buffer[200];
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
	int	actual_return_value = ft_printf("%100s", s);

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

MU_TEST(test_ft_printf_str_large_precision)
{
	// ARRANGE
	char	*s = "Hello";
	char	expected_output[] = "Hello";
	int	expected_return_value = 5;  // Expected number of characters printed
	char	buffer[200];
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
	int	actual_return_value = ft_printf("%.100s", s);

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

MU_TEST(test_ft_printf_str_large_width_and_precision)
{
	// ARRANGE
	char	*s = "Hello";
	char	expected_output[] = "                                                                                                 Hel";
	int	expected_return_value = 100;  // Expected number of characters printed
	char	buffer[200];
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
	int	actual_return_value = ft_printf("%100.3s", s);

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

MU_TEST(test_ft_printf_str_null_width_and_precision)
{
	// ARRANGE
	char	*s = NULL;
	char	expected_output[] = "       (nu";
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
	int	actual_return_value = ft_printf("%10.3s", s);

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

MU_TEST(test_ft_printf_str_empty_width_and_precision)
{
	// ARRANGE
	char	*s = "";
	char	expected_output[] = "          ";
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
	int	actual_return_value = ft_printf("%10.3s", s);

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

MU_TEST(test_ft_printf_str_with_text)
{
	// ARRANGE
	char	*s = "42";
	char	expected_output[] = "Hello 42 world!";
	int	expected_return_value = 15;  // Expected number of characters printed
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
	int	actual_return_value = ft_printf("Hello %s world!", s);

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

MU_TEST(test_ft_printf_str_invalid_flags)
{
	// ARRANGE
	char	*s = "Hello";
	char	expected_output[] = "Hello";
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
	int	actual_return_value = ft_printf("%+s", s);

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

MU_TEST_SUITE(ft_printf_s_test_suite)
{
	MU_RUN_TEST(test_ft_printf_one_string);
	MU_RUN_TEST(test_ft_printf_two_strings);
	MU_RUN_TEST(test_ft_printf_str_with_width_of_10);
	MU_RUN_TEST(test_ft_printf_str_with_width_and_left_aligned);
	MU_RUN_TEST(test_ft_printf_str_with_precision);
	MU_RUN_TEST(test_ft_printf_str_with_width_and_precision);
	MU_RUN_TEST(test_ft_printf_str_with_width_and_precision_and_left_aligned);
	MU_RUN_TEST(test_ft_printf_str_flag_null_pointer);
	MU_RUN_TEST(test_ft_printf_str_empty_string);
	MU_RUN_TEST(test_ft_printf_str_width_smaller_than_string_length);
	MU_RUN_TEST(test_ft_printf_str_precision_greater_than_string_length);
	MU_RUN_TEST(test_ft_printf_str_large_width);
	MU_RUN_TEST(test_ft_printf_str_large_precision);
	MU_RUN_TEST(test_ft_printf_str_large_width_and_precision);
	MU_RUN_TEST(test_ft_printf_str_null_width_and_precision);
	MU_RUN_TEST(test_ft_printf_str_empty_width_and_precision);
	MU_RUN_TEST(test_ft_printf_str_with_text);
	MU_RUN_TEST(test_ft_printf_str_invalid_flags);
}
