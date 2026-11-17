/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <ppoco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-13 18:33:43 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-13 18:33:43 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

/*Constants Used*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 122
# endif

/*The Actual Thing*/
char		*get_next_line(int fd);

/*  Utils  */
char		*grab_joined_buffer(char *static_buffer, int fd);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char *s1, const char *s2);
char		*ft_substr(const char *s, size_t start, size_t len);

#endif
