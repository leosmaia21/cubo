/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:02:53 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/03/25 22:03:04 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/libft/libft.h"
#include "includes.h"
#include <fcntl.h>

t_list	*getlines(int fd)
{
	t_list	*head;
	t_list	*current;
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		return (0);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = 0;
	head = ft_lstnew(line);
	current = head;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		current->next = malloc(sizeof(t_list));
		current = current->next;
		current->content = line;
		current->next = 0;
	}
	close(fd);
	return (head);
}

void	parser(char *name)
{
	int		fd;
	t_list	*lines;

	fd = open(name, O_RDONLY);
	lines = getlines(fd);
	while (lines)
	{
		printf("%s\n", lines->content);
		lines = lines->next;
	}
}
