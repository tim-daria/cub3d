/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:05:06 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/13 20:00:57 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Prints "Error" by default folleewd by an optional message (can be changed to print to STDERR)
bool	print_error(char *msg)
{
	printf("Error\n");
	if (msg)
		printf("%s\n", msg);
	return (false);
}
