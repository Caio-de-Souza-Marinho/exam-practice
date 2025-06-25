#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdio.h>

#include <stdarg.h>
#include <unistd.h>

int	ft_printf(const char *format, ...);
int	specifier_process(char specifier, va_list ap);
int	ft_putchar_printf(char c, int fd);
int	ft_putstr_printf(char *s, int fd);
int	ft_putnbr_printf(int nbr, int fd);
int	ft_puthex_printf(unsigned int nbr, int fd);

#endif // !FT_PRINTF_H
