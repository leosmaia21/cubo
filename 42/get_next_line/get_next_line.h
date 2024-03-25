/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:52:07 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/03/25 22:00:25 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

// void		*ft_calloc(size_t nmemb, size_t size);
// int			ft_strlen(const char *s);
// char		*ft_strjoin(char *s1, char *s2);
// char		*ft_strchr(const char *s, int c);
// s	ft_strlcpy(char *dst, const char *src, size_t size);
char		*get_next_line(int fd);
// void		*ft_bzero(void *s, int n);
#endif
