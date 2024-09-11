/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:05:14 by meghribe          #+#    #+#             */
/*   Updated: 2024/09/08 00:37:55 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	((unsigned char *)ptr)[0] = 0;
	((unsigned char *)ptr)[(nmemb * size) - 1] = 0;
	return (ptr);
}

static char	*get_line_from_buffer(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = gnl_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	gnl_strlcpy(line, buffer, i + 2);
	return (line);
}

static char	*keep_remaining_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = gnl_calloc(gnl_strlen(buffer) - i, sizeof(char));
	if (!new_buffer)
		return (NULL);
	gnl_strlcpy(new_buffer, &buffer[i + 1], gnl_strlen(buffer) - i);
	free(buffer);
	return (new_buffer);
}

static char	*fill_buffer(int fd, char *buffer)
{
	char		*tmp_buffer;
	int			bytes_count;

	tmp_buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp_buffer)
		return (NULL);
	bytes_count = 1;
	while (!gnl_strchr(buffer, '\n') && bytes_count != 0)
	{
		bytes_count = read(fd, tmp_buffer, BUFFER_SIZE);
		if (bytes_count == -1)
		{
			free(buffer);
			free(tmp_buffer);
			return (NULL);
		}
		tmp_buffer[bytes_count] = '\0';
		buffer = gnl_strjoin(buffer, tmp_buffer);
	}
	free(tmp_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd >= OPEN_MAX)
		return (NULL);
	buffer = fill_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	new_line = get_line_from_buffer(buffer);
	buffer = keep_remaining_buffer(buffer);
	return (new_line);
}
