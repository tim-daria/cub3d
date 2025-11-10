/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:05:06 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 15:25:03 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Prints "Error" by default folleewd by an optional message
//(can be changed to print to STDERR)
bool	print_error(char *msg)
{
	printf("❌ Error\n");
	if (msg)
		printf("%s\n", msg);
	return (false);
}
