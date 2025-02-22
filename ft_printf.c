/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:08:18 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/19 19:08:21 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdarg.h>

int	check_formate(va_list args, const char *format, int i, int fd)
{
	int		count;
	int		num;
	char	*str;
	char	c;

	count = 0;
	if (format[i] == 'd')
	{
		num = va_arg(args, int);
		ft_putnbr_fd(num, fd);
		count++;
	}
	else if (format[i] == 's')
	{
		str = va_arg(args, char *);
		ft_putstr_fd(str, fd);
		count++;
	}
	else if (format[i] == 'c')
	{
		c = va_arg(args, int);
		ft_putchar_fd(c, fd);
		count++;
	}
	return (count);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += check_formate(args, format, i, fd);
		}
		else
		{
			ft_putchar_fd(format[i], fd);
		}
		i++;
	}
	return (va_end(args), count);
}
