/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:30:32 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 18:18:02 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check if path ends with .xpm, if not append it
char	*check_and_fix_texture_path(char *path)
{
	char	*fixed_path;
	int		len;

	if (!path)
		return (NULL);
	len = ft_strlen(path);
	if (len >= 4 && ft_strcmp(path + len - 4, ".xpm") == 0)
		return (ft_strdup(path));
	fixed_path = ft_strjoin(path, ".xpm");
	if (!fixed_path)
		return (NULL);
	return (fixed_path);
}
