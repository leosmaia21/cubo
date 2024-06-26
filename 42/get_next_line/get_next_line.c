/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:14:04 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/03/25 22:01:03 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

char	*read_line(int fd, char *buf)
{
	char	*aux;
	char	*temp;
	int		b_read;

	b_read = 1;
	aux = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (b_read != 0 && !ft_strchr(buf, '\n'))
	{
		b_read = read(fd, aux, BUFFER_SIZE);
		if (b_read < 0)
		{
			free(aux);
			return (NULL);
		}
		if (!buf)
			buf = ft_calloc(1, 1);
		temp = ft_strjoin(buf, aux);
		ft_bzero(aux, BUFFER_SIZE + 1);
		free(buf);
		buf = temp;
	}
	free(aux);
	return (buf);
}

char	*get_line(char	*buf)
{
	int		i;
	int		newindex;
	char	*line;

	newindex = -1;
	i = 0;
	if (!buf[0])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		line = ft_calloc(i + 2, sizeof(char));
	else if (buf[i] == 0)
		line = ft_calloc(i + 1, sizeof(char));
	while (++newindex < i + 1)
		line[newindex] = buf[newindex];
	return (line);
}

char	*shiftbuffer(char *buf)
{
	int		i;
	char	*newbuf;
	int		newindex;

	newindex = 0;
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == 0)
	{
		free(buf);
		return (NULL);
	}
	newbuf = ft_calloc(ft_strlen(buf) - i + 1, sizeof(char));
	if (buf[i] == '\n')
		i++;
	while (buf[i])
		newbuf[newindex++] = buf[i++];
	free(buf);
	return (newbuf);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = shiftbuffer(buffer);
	return (line);
}

/* int main(void) */
/* { */
/* 	int fd = open ("gnlTester/files/multiple_nlx5", O_RDONLY); */
/* 	printf("%s",get_next_line(fd)); */
/* 	printf("%s",get_next_line(fd)); */
/* 	printf("%s",get_next_line(fd)); */
/* 	printf("%s",get_next_line(fd)); */
/* 	printf("%s",get_next_line(fd)); */
/* 	printf("%s",get_next_line(fd)); */
/* 	return 0; */
/* } */
