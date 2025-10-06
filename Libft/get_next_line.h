/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:14:28 by dtimofee          #+#    #+#             */
/*   Updated: 2025/03/12 14:16:50 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

typedef struct Array
{
	unsigned int	size;
	char			*main_buf;
}	t_array;

char	*get_next_line(int fd);
char	*gnl_substr(char const *s, size_t len);
void	*gnl_memcpy(char *dest, const char *src, size_t n);
int		gnl_strchr(char *s);
size_t	gnl_strlen(const char *s);

#endif
