/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-13 18:33:30 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-13 18:33:30 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (size && i + 1 < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (free(s1), NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		++j;
		++i;
	}
	free(s1);
	str[i] = '\0';
	return (str);
}

char	*ft_substr(const char *s, size_t start, size_t len)
{
	char	*substr;
	size_t	len_s;
	size_t	i;

	if (!s || !len)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		len = 0;
	if (len > len_s - start)
		len = len_s - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		substr[i] = s[start];
		++start;
		++i;
	}
	substr[i] = '\0';
	return (substr);
}

char	*grab_joined_buffer(char *buffer, int fd)
{
	char	*joined;
	ssize_t	i;

	joined = ft_substr(buffer, 0, ft_strlen(buffer) + 1);
	while (joined)
	{
		i = 0;
		while (joined[i] && joined[i] != '\n')
			i++;
		if (joined[i] == '\n')
			return (joined);
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0 || (!i && !joined[0]))
			return (free(joined), NULL);
		if (!i)
			return (joined);
		buffer[i] = '\0';
		joined = ft_strjoin(joined, buffer);
	}
	return (NULL);
}
