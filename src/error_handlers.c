/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:05:06 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/25 14:11:33 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Prints "Error" by default folleewd by an optional message
//(can be changed to print to STDERR)
bool	print_error(char *msg)
{
	ft_putendl_fd("❌ Error", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	return (false);
}
