/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:11:51 by caide-so          #+#    #+#             */
/*   Updated: 2024/11/24 21:28:26 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <stdio.h>

int	main(void)
{
	int	num1 = 42;
	int	num2 = -42;
	ft_printf("[%50d]\n", num1);
	printf("[%50d]\n", num1);

	ft_printf("[%50d]\n", num2);
	printf("[%50d]\n", num2);
}
