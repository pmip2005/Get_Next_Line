/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   azy\Docus\Code\Test\get_next_line\get_next.c:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppoco <marvin.42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-11-10 22:12:21 by ppoco             #+#    #+#             */
/*   Updated: 2026-11-10 22:12:21 by ppoco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

/*Constants Used*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
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
