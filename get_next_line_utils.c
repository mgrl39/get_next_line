/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:05:36 by meghribe          #+#    #+#             */
/*   Updated: 2024/09/08 00:37:55 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	gnl_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = gnl_strlen(dst);
	src_len = gnl_strlen(src);
	if (size <= dst_len)
		return (src_len + size);
	gnl_strlcpy(&dst[dst_len], src, size - dst_len);
	return (dst_len + src_len);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	if (!dst || !src)
		return (0);
	src_len = gnl_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	s1_len;
	size_t	s2_len;

	if (!s2)
		return (NULL);
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	s3 = gnl_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!s3)
		return (NULL);
	gnl_strlcpy(s3, s1, s1_len + 1);
	gnl_strlcat(s3, s2, s1_len + s2_len + 1);
	free(s1);
	return (s3);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (((unsigned char *)s)[i] != '\0')
		if (((unsigned char *)s)[i++] == (unsigned char)c)
			return ((char *)&s[--i]);
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
