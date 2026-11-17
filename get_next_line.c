/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-13 18:33:36 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-13 18:33:36 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*feed;
	char		*this_line;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	feed = grab_joined_buffer(buffer, fd);
	if (!feed)
		return (buffer[0] = '\0', NULL);
	i = 0;
	while (feed[i] && feed[i] != '\n')
		i++;
	if (feed[i] == '\n')
		i++;
	this_line = ft_substr(feed, 0, i);
	if (!this_line)
		return (free(feed), buffer[0] = '\0', NULL);
	return (ft_strlcpy(buffer, feed + i, BUFFER_SIZE + 1),
		free(feed), this_line);
}
