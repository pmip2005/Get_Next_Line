/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-12 15:08:12 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-12 15:08:12 by ppoco            ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		++i;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
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

char	*grab_joined_buffer(char *static_buffer, int fd)
{
	char	temp[BUFFER_SIZE + 1];
	ssize_t	i;

	i = 0;
	while (i <= BUFFER_SIZE)
	{
		temp[i] = 0;
		i++;
	}
	i = 1;
	while (i && (!static_buffer || !ft_strchr(static_buffer, '\n')))
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i < 0 || (!i && !static_buffer))
			return (free(static_buffer), NULL);
		temp[i] = '\0';
		if (!static_buffer)
			static_buffer = ft_substr(temp, 0, ft_strlen(temp));
		else
			static_buffer = ft_strjoin(static_buffer, temp);
		if (!static_buffer)
			return (free(static_buffer), NULL);
	}
	return (static_buffer);
}
