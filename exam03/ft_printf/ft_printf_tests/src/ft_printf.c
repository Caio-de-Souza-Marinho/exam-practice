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

#include <limits.h>

#include "ft_printf.h"

int	main(void)
{
	char *str = NULL;
	ft_printf("Normal string - %s\nEmpty string - %s\nNULL string - %s\n", "ola meu nome 'e caio", "", str);
	printf("Normal string - %s\nEmpty string - %s\nNULL string - %s\n", "ola meu nome 'e caio", "", str);

	ft_printf("INT MAX - %d\nINT MIN - %d\n", INT_MAX, INT_MIN);
	printf("INT MAX - %d\nINT MIN - %d\n", INT_MAX, INT_MIN);

	ft_printf("Hex 255 - %x\nHex 42 - %x\nHex 0 - %d\nHex -1 - %d\n", 255, 42, 0, -1);
	printf("Hex 255 - %x\nHex 42 - %x\nHex 0 - %d\nHex -1 - %d\n", 255, 42, 0, -1);

	return (0);
}

/*
stdarg.h, unistd.h
va_list ap;
va_start(ap, format string)
loop format string
	find '%'
		process specifiers
			if s
				putstr
			if d
				putnbr
			if x
				puthex
va_end(ap)
return (count)
*/

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
			count += specifier_process(format[i + 1], ap);
			i++;
		}
		else
			count += ft_putchar_printf(format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}

int	specifier_process(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 's')
		count += ft_putstr_printf(va_arg(ap, char*), 1);
	else if (specifier == 'd')
		count += ft_putnbr_printf(va_arg(ap, int), 1);
	else if (specifier == 'x')
		count += ft_puthex_printf(va_arg(ap, unsigned int), 1);
	return (count);
}

int	ft_putchar_printf(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr_printf(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return write(fd, "(null)", 6);
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr_printf(int nbr, int fd)
{
	int	count;
	long	num;

	count = 0;
	num = nbr;
	if (num < 0)
	{
		count += ft_putchar_printf('-', fd);
		num = -num;
	}
	if (num >= 10)
		count += ft_putnbr_printf(num / 10, fd);
	count += ft_putchar_printf((num % 10) + '0', fd);
	return (count);
}

int	ft_puthex_printf(unsigned int nbr, int fd)
{
	int	count;

	count = 0;
	if (nbr >= 16)
		count += ft_puthex_printf(nbr / 16, fd);
	count += ft_putchar_printf("0123456789abcdef"[nbr % 16], fd);
	return (count);
}
