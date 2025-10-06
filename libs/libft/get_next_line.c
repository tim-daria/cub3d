/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:57:48 by dtimofee          #+#    #+#             */
/*   Updated: 2025/03/13 19:35:18 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*doubble_buf(t_array *a, char *buf)
{
	char	*new_buf;

	new_buf = malloc((a->size + 1) * sizeof(char));
	if (new_buf == NULL)
	{
		free(a->main_buf);
		free(buf);
		return (NULL);
	}
	gnl_memcpy(new_buf, a->main_buf, a->size / 2 + 1);
	free(a->main_buf);
	return (new_buf);
}

static char	*finalize_buf(t_array *a, ssize_t currently_read_size,
		size_t len, char *buf)
{
	char	*current_line;

	if (currently_read_size == 0 && len > 0)
	{
		current_line = gnl_substr(a->main_buf, len);
		a->main_buf[0] = '\0';
		free(buf);
		if (current_line == NULL)
		{
			free(a->main_buf);
			a->main_buf = NULL;
			a->size = 0;
		}
		return (current_line);
	}
	free(buf);
	free(a->main_buf);
	a->main_buf = NULL;
	a->size = 0;
	return (NULL);
}

static char	*return_line(t_array *a, int position)
{
	char			*current_line;
	unsigned int	j;
	size_t			len;

	len = gnl_strlen(a->main_buf);
	current_line = gnl_substr(a->main_buf, position + 1);
	if (current_line == NULL)
	{
		free(a->main_buf);
		a->main_buf = NULL;
		a->size = 0;
		return (current_line);
	}
	j = 0;
	while ((size_t) position + 1 <= len)
		a->main_buf[j++] = a->main_buf[position++ + 1];
	return (current_line);
}

static char	*read_line(t_array *a, int fd)
{
	char	*buf;
	ssize_t	currently_read_size;
	int		position;
	size_t	len;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while ((gnl_strchr(a->main_buf)) == -1)
	{
		len = gnl_strlen(a->main_buf);
		currently_read_size = read(fd, buf, BUFFER_SIZE);
		if (currently_read_size <= 0)
			return (finalize_buf(a, currently_read_size, len, buf));
		buf[currently_read_size] = '\0';
		if (a->size < len + currently_read_size + 1)
		{
			a->size *= 2;
			a->main_buf = doubble_buf(a, buf);
			if (a->main_buf == NULL)
				return (NULL);
		}
		gnl_memcpy(a->main_buf + len, buf, currently_read_size + 1);
	}
	free(buf);
	position = gnl_strchr(a->main_buf);
	return (return_line(a, position));
}

char	*get_next_line(int fd)
{
	static t_array	a;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
	{
		if (a.main_buf != NULL)
			free(a.main_buf);
		return (NULL);
	}
	if (a.main_buf == NULL)
	{
		a.size = BUFFER_SIZE;
		a.main_buf = malloc((a.size + 1) * sizeof(char));
		if (a.main_buf == NULL)
			return (NULL);
		a.main_buf[0] = '\0';
	}
	return (read_line(&a, fd));
}
