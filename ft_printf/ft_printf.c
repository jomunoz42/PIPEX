/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:37:25 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/11 23:31:41 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


static int	printf_type(char s, va_list args)
{
	if (s == 'c')
		return (ft_putchar_count(va_arg(args, int)));
	if (s == 's')
		return (ft_putstr_count(va_arg(args, char *)));
	if (s == 'd' || s == 'i')
		return (ft_putnbr_count(va_arg(args, int)));
	if (s == 'u')
		return (ft_putunbr_count(va_arg(args, unsigned int)));
	if (s == 'x')
		return (ft_hexa_lower(va_arg(args, unsigned int)));
	if (s == 'X')
		return (ft_hexa_upper(va_arg(args, unsigned int)));
	if (s == 'p')
		return (ft_pointer_hexa(va_arg(args, void *)));
	if (s == '%')
		return (ft_putchar_count('%'));
	return (-1);
}

static int	is_valid_specifier(char c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'u' || c == 'x'
		|| c == 'X' || c == 'p' || c == '%')
		return (1);
	return (0);
}

static int	is_count_valid(int count)
{
	if (count < 0)
		return (-1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	if (format == NULL)
		return (-1);
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%' && *(format + 1) == '\0')
			return (va_end(args), -1);
		if (*format == '%')
		{
			format++;
			if (*format && is_valid_specifier(*format) == 1)
				count += printf_type(*format, args);
			else if (*format)
				count += ft_putchar_count('%') + ft_putchar_count(*format);
		}
		else
			count += ft_putchar_count(*format);
		format++;
	}
	va_end(args);
	return (is_count_valid(count));
}
