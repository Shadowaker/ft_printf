/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:51:41 by dridolfo          #+#    #+#             */
/*   Updated: 2022/01/24 16:06:59 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

static int	ft_filter(va_list *arg, char c, int i)
{
	if (c == 'c')
		i += ft_putchar(va_arg(*arg, int));
	else if (c == 's')
		i += ft_putstr(va_arg(*arg, char *));
	else if (c == 'p')
	{
		i += ft_putp(va_arg(*arg, unsigned long int));
	}
	else if (c == 'd' || c == 'i' || c == 'u')
	{
		if (c == 'd' || c == 'i')
			i += ft_putnbr_base(va_arg(*arg, int), "0123456789");
		else
			i += ft_putuns(va_arg(*arg, unsigned long long int));
	}
	else if (c == 'x')
		i += ft_putnbr_base(va_arg(*arg, long long int), "0123456789abcdef");
	else if (c == 'X')
		i += ft_putnbr_base(va_arg(*arg, long long int), "0123456789ABCDEF");
	else if (c == '%')
		i += ft_putchar('%');
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		i;
	int		re;

	va_start(arg, format);
	i = 0;
	re = 0;
	while (format[i] != '\0')
	{
		if ('%' == ((char *) format)[i])
		{
			re = ft_filter(&arg, ((char *) format)[i + 1], re);
			i++;
		}
		else
		{
			ft_putchar(format[i]);
			re++;
		}
		i++;
	}
	va_end(arg);
	return (re);
}

int	main(void)
{
	int		re1;
	int		re2;
	void	*p;

	p = 0;
	re1 = ft_printf("pollo $%c$ pollo\n", 'p');
	re2 = printf("pollo $%c$ pollo\n", 'p');
	printf("ft_printf: %d\nprintf: %d\n", re1, re2);
	printf("------------------------------------\n");
	re1 = ft_printf("pollo $%s$ pollo\n", "culo");
	re2 = printf("pollo $%s$ pollo\n", "culo");
	printf("ft_printf: %d\nprintf: %d\n", re1, re2);
	printf("------------------------------------\n");
	re1 = ft_printf("pollo $%d$ pollo\n", 12);
	re2 = printf("pollo $%d$ pollo\n", 12);
	printf("ft_printf: %d\nprintf: %d\n", re1, re2);
	printf("------------------------------------\n");
	re1 = ft_printf("pollo $%i$ pollo\n", -12);
	re2 = printf("pollo $%i$ pollo\n", -12);
	printf("ft_printf: %d\nprintf: %d\n", re1, re2);
	printf("------------------------------------\n");
	re1 = ft_printf("pollo $%u$ pollo\n", 12);
	re2 = printf("pollo $%u$ pollo\n", 12);
	printf("ft_printf: %d\nprintf: %d\n", re1, re2);
	printf("------------------------------------\n");
	re1 = ft_printf("pollo $%%$ pollo\n");
	re2 = printf("pollo $%%$ pollo\n");
	printf("ft_printf: %d\nprintf: %d\n", re1, re2);
	printf("------------------------------------\n");
	re1 = ft_printf("pollo $%x$ pollo\n", 1234);
	re2 = printf("pollo $%x$ pollo\n", 1234);
	printf("ft_printf: %d\nprintf: %d\n", re1, re2);
	printf("------------------------------------\n");
	re1 = ft_printf("pollo $%X$ pollo\n", -1234);
	re2 = printf("pollo $%X$ pollo\n", -1234);
	printf("ft_printf: %d\nprintf: %d\n", re1, re2);
	printf("------------------------------------\n");
	re1 = ft_printf("pollo $%p$ pollo\n", p);
	re2 = printf("pollo $%p$ pollo\n", p);
	printf("ft_printf: %d\nprintf: %d\n", re1, re2);
	printf("------------------------------------\n");
}
