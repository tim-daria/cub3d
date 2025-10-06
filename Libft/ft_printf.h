/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:26:09 by dtimofee          #+#    #+#             */
/*   Updated: 2024/12/09 11:49:03 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	conversion_c(int c);
int	conversion_s(char *str);
int	conversion_num(char c, long long num);
int	conversion_p(unsigned long long ptr);

#endif
