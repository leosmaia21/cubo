/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:02:53 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/04/01 22:18:52 by ledos-sa         ###   ########.fr       */
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

int	parsecords(char **line, cubo *cubo)
{
	if (line[3] == 0)
		return (0);
	if (!ft_strcmp(line[0], "NO") && cubo->NO == 0)
		cubo->NO = ft_strdup(line[1]);
	else if (!ft_strcmp(line[0], "SO") && cubo->SO == 0)
		cubo->SO = ft_strdup(line[1]);
	else if (!ft_strcmp(line[0], "WE") && cubo->WE == 0)
		cubo->WE = ft_strdup(line[1]);
	else if (!ft_strcmp(line[0], "EA") && cubo->EA == 0)
		cubo->EA = ft_strdup(line[1]);
	else
		return (0);
	return (1);
}

void	freedouble(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	insertcolorcubo(cubo *cubo, int *colors, char **line)
{
	if (!ft_strcmp(line[0], "F"))
	{
		cubo->F[0] = colors[0];
		cubo->F[1] = colors[1];
		cubo->F[2] = colors[2];
	}
	else if (!ft_strcmp(line[0], "C"))
	{
		cubo->C[0] = colors[0];
		cubo->C[1] = colors[1];
		cubo->C[2] = colors[2];
	}
}

int	parsecolor(cubo *cubo, char **line)
{
	char	**split;
	int		colors[3];

	split = ft_split(line[1], ',');
	if (!split[0] || !split[1] || !split[2])
	{
		freedouble(split);
		return (0);
	}
	colors[0] = ft_atoi(split[0]);
	colors[1] = ft_atoi(split[1]);
	colors[2] = ft_atoi(split[2]);
	if (colors[0] < 0 || colors[0] > 255 || colors[1] < 0 || \
		colors[1] > 255 || colors[2] < 0 || colors[2] > 255)
	{
		freedouble(split);
		return (0);
	}
	insertcolorcubo(cubo, colors, line);
	freedouble(split);
	return (1);
}

int	parsefirstlines(t_list *lines, cubo *cubo)
{
	t_list	*current;
	int		stage;
	char	**content;
	int		ret;

	current = lines;
	stage = 0;
	ret = 0;
	while (current && ret < 6)
	{
		content = ft_split(current->content, ' ');
		if (content[0][0] == '1' && content[0][0] == '0')
		{
			freedouble(content);
			return (0);
		}
		else if (content && content[0] && content[0][0])
		{
			if (!ft_strcmp(content[0], "NO"))
				ret += parsecords(content, cubo);
			else if (!ft_strcmp(content[0], "SO"))
				ret += parsecords(content, cubo);
			else if (!ft_strcmp(content[0], "WE"))
				ret += parsecords(content, cubo);
			else if (!ft_strcmp(content[0], "EA"))
				ret += parsecords(content, cubo);
			else if (!ft_strcmp(content[0], "F"))
				ret += parsecolor(cubo, content);
			else if (!ft_strcmp(content[0], "C"))
				ret += parsecolor(cubo, content);
		}
		freedouble(content);
		current = current->next;
	}
	return (ret);
}

//floofill return 1 if the map is valid
//floofill return 0 if the map is invalid
int	floodfill(char **map, int x, int y)
{
	if (map[y][x] == '1')
		return (1);
	if (map[y][x] == ' ')
	{
		map[y][x] = '1';
		if (!floodfill(map, x + 1, y))
			return (0);
		if (!floodfill(map, x - 1, y))
			return (0);
		if (!floodfill(map, x, y + 1))
			return (0);
		if (!floodfill(map, x, y - 1))
			return (0);
	}
	return (1);
}

void	initcube(cubo *cubo)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	cubo->NO = 0;
	cubo->SO = 0;
	cubo->WE = 0;
	cubo->EA = 0;
	cubo->F[0] = -1;
	cubo->F[1] = -1;
	cubo->F[2] = -1;
	cubo->C[0] = -1;
	cubo->C[1] = -1;
	cubo->C[2] = -1;
	while (++i < 8192)
	{
		j = -1;
		while (++j < 8192)
			cubo->map[i][j] = -1;
	}
}

//falta fazer o insert do mapa
void	insertmap(char **map, cubo *cubo)
{
	int	i;
	int	j;
	char

	i = -1;
	j = -1;

}

cubo	*parser(char *name)
{
	int		fd;
	t_list	*lines;
	cubo	*c;
	int ret;

	c = malloc(sizeof(cubo));
	initcube(c);
	fd = open(name, O_RDONLY);
	lines = getlines(fd);
	ret = parsefirstlines(lines, c);
	if (ret < 6)
	{
		ft_lstclear(&lines, free);
		free(c);
		return (0);
	}

}
