/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:24:22 by zdidah            #+#    #+#             */
/*   Updated: 2025/01/03 21:21:37 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr(unsigned int n,int fd)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putunbr(n / 10,fd);
	count += ft_putchar(n % 10 + '0', fd);
	return (count);
}

void	check(const char format, va_list args, int *count,int fd)
{
	if (format == 'c')
		*count += ft_putchar(va_arg(args, int),fd);
	else if (format == 's')
		*count += ft_putstr(va_arg(args, char *),fd);
	else if (format == 'd' || format == 'i')
		*count += ft_putnbr(va_arg(args, int),fd);
	else if (format == 'u')
		*count += ft_putunbr(va_arg(args, unsigned int),fd);
	else if (format == 'x')
		*count += ft_puthex(va_arg(args, unsigned int), 0,fd);
	else if (format == 'X')
		*count += ft_puthex(va_arg(args, unsigned int), 1,fd);
	else if (format == 'p')
		*count += ft_putptr(va_arg(args, unsigned long), 1,fd);
	else if (format == '%')
		*count += ft_putchar('%',fd);
}

int	ft_printf(int fd ,const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, format);
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			check(format[i], args, &count, fd);
		}
		else
			count += ft_putchar(format[i], fd);
		i++;
	}
	va_end(args);
	return (count);
}
