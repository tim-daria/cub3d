/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:07:27 by dtimofee          #+#    #+#             */
/*   Updated: 2024/12/09 12:07:27 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*definition_base(char c)
{
	if (c == 'x' || c == 'p')
		return ("0123456789abcdef");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	else
		return (0);
}

static int	ft_putnbr(unsigned int base, char *str_base, long long num)
{
	unsigned int	i;
	unsigned int	count;
	char			write_num[30];

	i = 0;
	count = 0;
	if (num < 0)
	{
		num *= (-1);
		write(1, "-", 1);
		count++;
	}
	if (num == 0)
		write_num[i++] = str_base[0];
	while (num > 0)
	{
		write_num[i++] = str_base[num % base];
		num = num / base;
	}
	count += i;
	while (i > 0)
		write(1, &write_num[(i--) - 1], 1);
	return (count);
}

int	conversion_num(char c, long long num)
{
	char			*str_base;
	unsigned int	base;

	base = 10;
	str_base = "0123456789";
	if (c == 'x' || c == 'X')
	{
		base = 16;
		str_base = definition_base(c);
	}
	return (ft_putnbr(base, str_base, num));
}

int	conversion_p(unsigned long long ptr)
{
	unsigned int	count;
	unsigned int	i;
	char			*str_base;
	char			write_ptr[30];

	if (ptr == 0)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	str_base = definition_base('p');
	i = 0;
	while (ptr > 0)
	{
		write_ptr[i++] = str_base[ptr % 16];
		ptr = ptr / 16;
	}
	count += i;
	while (i > 0)
		write(1, &write_ptr[(i--) - 1], 1);
	return (count);
}
