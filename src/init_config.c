/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:37:50 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/12 21:50:37 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config	*init_config(void)
{
	t_config	*new;
	int			i;

	new = malloc(sizeof(t_config));
	if (!new)
		return (NULL);
	i = NORTH;
	while (i <= EAST)
	{
		new->textures[i] = NULL;
		i++;
	}
	new->floor_color = -1;
	new->ceiling_color = -1;
	return (new);
}

void	free_config(t_config *config)
{
	int	i;

	if (!config)
		return ;
	i = NORTH;
	while (i <= EAST)
	{
		if (config->textures[i])
			free(config->textures[i]);
		i++;
	}
	free(config);
}