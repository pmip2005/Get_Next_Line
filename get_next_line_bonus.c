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

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*remaining_buff[OPEN_MAX];
	char		*temp;
	char		*this_line;
	size_t		i;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	remaining_buff[fd] = grab_joined_buffer(remaining_buff[fd], fd);
	if (!remaining_buff[fd] || !remaining_buff[fd][0])
		return (NULL);
	i = 0;
	while (remaining_buff[fd][i] && remaining_buff[fd][i] != '\n')
		i++;
	if (remaining_buff[fd][i] == '\n')
		i++;
	this_line = ft_substr(remaining_buff[fd], 0, i);
	temp = NULL;
	if (this_line && remaining_buff[fd][i])
		temp = ft_substr(remaining_buff[fd], i, ft_strlen(remaining_buff[fd]));
	if (!this_line || (remaining_buff[fd][i] && !temp))
		return (free(this_line), free(remaining_buff[fd]),
			remaining_buff[fd] = NULL, NULL);
	free(remaining_buff[fd]);
	remaining_buff[fd] = temp;
	return (this_line);
}
