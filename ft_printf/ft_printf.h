/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:24:50 by zdidah            #+#    #+#             */
/*   Updated: 2025/01/03 21:22:50 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(int fd, const char *format, ...);
int		ft_putchar(char c,int fd);
int		ft_putstr(const char *s,int fd);
int		ft_putnbr(int n,int fd);
int		ft_puthex(unsigned int n, int upper,int fd);
int		ft_putptr(unsigned long n, int k,int fd);
int		ft_putunbr(unsigned int n,int fd);
void	check(const char format, va_list args, int *count,int fd);

#endif