/*
Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Write a function named `ft_printf` that will mimic the real printf but 
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.

Exemples of the function output:

call: ft_printf("%s\n", "toto");
out: toto$

call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$

Obs: Your function must not have memory leaks. Moulinette will test that.
*/

#include <stdarg.h>
#include <unistd.h>

#include <stdio.h>
#include <limits.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(char c, int fd);
int	specifier_formater(char specifier, va_list ap);
int	ft_putstr(char *str, int fd);
int	ft_putnbr(int nbr, int fd);
int	ft_puthex(unsigned int nbr, int fd);

int	main(void)
{
	char *str = NULL;
	ft_printf("Normal string: %s\n", "caio legal");
	printf("Normal string: %s\n", "caio legal");
	ft_printf("Empty string %s\n", "");
	printf("Empty string %s\n", "");
	ft_printf("NULL %s\n", str);
	printf("NULL %s\n", str);

	ft_printf("INT MAX: %d\n", INT_MAX);
	printf("INT MAX: %d\n", INT_MAX);
	ft_printf("INT MIN %d\n", INT_MIN);
	printf("INT MIN %d\n", INT_MIN);

	ft_printf("Hex 255: %x\n", 255);
	printf("Hex 255: %x\n", 255);
	ft_printf("Hex 42: %x\n", 42);
	printf("Hex 42: %x\n", 42);
	ft_printf("Hex 0: %x\n", 0);
	printf("Hex 0: %x\n", 0);
	ft_printf("Hex -1: %x\n", -1);
	printf("Hex -1: %x\n", -1);
	
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int	count;
	int	i;
	va_list	ap;

	count = 0;
	i = 0;
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			count += specifier_formater(format[i + 1], ap);
			i++;
		}
		else
			count += ft_putchar(format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}

int	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	specifier_formater(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 's')
		count += ft_putstr(va_arg(ap, char *), 1);
	else if (specifier == 'd')
		count += ft_putnbr(va_arg(ap, int), 1);
	else if (specifier == 'x')
		count += ft_puthex(va_arg(ap, unsigned int), 1);
	return (count);
}

int	ft_putstr(char *str, int fd)
{
	int	i;

	if (str == NULL)
		return (ft_putstr("(null)", fd));
	i = 0;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int nbr, int fd)
{
	long	num;
	int	count;

	count = 0;
	num = nbr;
	if (num < 0)
	{
		count += ft_putchar('-', fd);
		num = -num;
	}
	if (num >= 10)
		count += ft_putnbr((num / 10), fd);
	count += ft_putchar((num % 10) + '0', fd);
	return (count);
}

int	ft_puthex(unsigned int nbr, int fd)
{
	int	count;

	count = 0;
	if (nbr >= 16)
		count += ft_puthex((nbr / 16), fd);
	count += ft_putchar("0123456789abcdef"[nbr % 16], fd);
	return (count);
}
