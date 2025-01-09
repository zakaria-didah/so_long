/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:26:26 by zdidah            #+#    #+#             */
/*   Updated: 2025/01/03 19:31:12 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr(const char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)",fd));
	while (s[i])
		i += ft_putchar(s[i] , fd);
	return (i);
}

int	ft_putnbr(int n, int fd)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648",fd));
	if (n < 0)
	{
		count += ft_putchar('-',fd);
		n *= -1;
	}
	if (n >= 10)
		count += ft_putnbr(n / 10,fd);
	count += ft_putchar(n % 10 + '0',fd);
	return (count);
}

int	ft_puthex(unsigned int n, int upper,int fd)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_puthex(n / 16, upper,fd);
	if (n % 16 < 10)
		count += ft_putchar((n % 16) + '0', fd);
	else
	{
		if (upper)
			count += ft_putchar(n % 16 - 10 + 'A',fd);
		else
			count += ft_putchar(n % 16 - 10 + 'a',fd);
	}
	return (count);
}

int	ft_putptr(unsigned long n, int k, int fd)
{
	int	count;

	count = 0;
	if (k)
		count += ft_putstr("0x",fd);
	if (n >= 16)
		count += ft_putptr(n / 16, 0,fd);
	count += ft_putchar("0123456789abcdef"[n % 16],fd);
	return (count);
}
