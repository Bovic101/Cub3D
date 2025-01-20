/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirmizi <tkirmizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:59:52 by vodebunm          #+#    #+#             */
/*   Updated: 2025/01/20 12:46:19 by tkirmizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/get_next_line.h"

void	free_null(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*join_line(int nl_position, char **buffer)
{
	char	*res;
	char	*tmp;

	tmp = NULL;
	if (nl_position <= 0)
	{
		if (**buffer == '\0')
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		res = *buffer;
		*buffer = NULL;
		return (res);
	}
	tmp = ft_substr(*buffer, nl_position, BUFFER_SIZE);
	res = *buffer;
	res[nl_position] = 0;
	*buffer = tmp;
	return (res);
}

char	*read_line(int fd, char **buffer, char *read_return, ssize_t br)
{
	char	*tmp;
	char	*nl;

	nl = ft_strchr(*buffer, '\n');
	tmp = NULL;
	while (nl == NULL)
	{
		br = read(fd, read_return, BUFFER_SIZE);
		if (br == -1)
		{
			free_null(buffer);
			return (NULL);
		}
		if (br <= 0)
			return (join_line(br, buffer));
		read_return[br] = 0;
		tmp = ft_strjoin(*buffer, read_return);
		if (tmp == NULL)
			return (NULL);
		free_null(buffer);
		*buffer = tmp;
		nl = ft_strchr(*buffer, '\n');
	}
	return (join_line(nl - *buffer + 1, buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD + 1];
	char		*read_return;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	read_return = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (read_return == NULL)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	res = read_line(fd, &buffer[fd], read_return, 0);
	free_null(&read_return);
	return (res);
}
