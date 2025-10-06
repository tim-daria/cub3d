/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:45:18 by dtimofee          #+#    #+#             */
/*   Updated: 2024/12/09 12:02:18 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conversion_c(int c)
{
	return (write(1, &c, 1));
}

static int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		count += write(1, &(*s), 1);
		s++;
	}
	return (count);
}

int	conversion_s(char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	return (ft_putstr(str));
}
