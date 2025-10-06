/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:41:12 by dtimofee          #+#    #+#             */
/*   Updated: 2024/12/19 16:56:44 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_memcpy(char *dest, const char *src, size_t n)
{
	unsigned int		i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*gnl_substr(char const *s, size_t len)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	gnl_memcpy(str, s, len);
	str[len] = '\0';
	return (str);
}

int	gnl_strchr(char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
