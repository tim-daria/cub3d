/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:29:08 by dtimofee          #+#    #+#             */
/*   Updated: 2024/12/10 15:12:26 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	correct_type(char type)
{
	char	*set;

	set = "cspdiuxX%";
	while (*set != '\0')
	{
		if (type == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	argument_type(char c, va_list ap)
{
	if (c == 'c')
		return (conversion_c(va_arg(ap, int)));
	else if (c == 's')
		return (conversion_s(va_arg(ap, char *)));
	else if (c == 'd' || c == 'i')
		return (conversion_num(c, va_arg(ap, int)));
	else if (c == 'u' || c == 'x' || c == 'X')
		return (conversion_num(c, va_arg(ap, unsigned int)));
	else if (c == 'p')
		return (conversion_p(va_arg(ap, unsigned long long)));
	else if (c == '%')
		return (conversion_c(c));
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && correct_type(*(format + 1)))
		{
			format++;
			count += argument_type(*format, ap);
		}
		else
			count += write(1, &(*format), 1);
		if (*format)
			format++;
	}
	va_end(ap);
	return (count);
}
