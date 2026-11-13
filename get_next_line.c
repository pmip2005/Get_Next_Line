/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-10 22:12:06 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-10 22:12:06 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*feed;
	char		*temp;
	char		*this_line;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	feed = grab_joined_buffer(feed, fd);
	if (!feed || !feed[0])
		return (NULL);
	i = 0;
	while (feed[i] && feed[i] != '\n')
		i++;
	if (feed[i] == '\n')
		i++;
	this_line = ft_substr(feed, 0, i);
	temp = NULL;
	if (this_line && feed[i])
		temp = ft_substr(feed, i, ft_strlen(feed));
	if (!this_line || (feed[i] && !temp))
		return (free(this_line), free(feed),
			feed = NULL, NULL);
	free(feed);
	feed = temp;
	return (this_line);
}
