/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:34:08 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/04/07 04:48:48 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	drawsquare(cubo *c, int x, int y, int color)
{
	int	yy;
	int	xx;

	yy = -1;
	while (++yy < TILESIZE)
	{
		xx = -1;
		while (++xx < TILESIZE)
		{
			mlx_pixel_put(c->vars.mlx, c->vars.win, x * TILESIZE + xx, y * TILESIZE + yy, color);
		}
	}
}

void	drawplayer(cubo *c)
{
	int	yy;
	int	xx;

	yy = -1;
	while (++yy < PLAYERSIZE)
	{
		xx = -1;
		while (++xx < PLAYERSIZE)
		{
			mlx_pixel_put(c->vars.mlx, c->vars.win, c->playerp[0] + xx, c->playerp[1] + yy, 0x00FF0000);
		}
	}
}

void drawanglepoint(cubo *c)
{
	int x;
	int y;

	x = c->playerp[0] + c->pdx * 4;
	y = c->playerp[1] + c->pdy * 4;
	mlx_pixel_put(c->vars.mlx, c->vars.win, x, y, 0x00FF0000);
}

void	drawmap(cubo *c)
{
	int	x;
	int	y;

	y = -1;
	while (++y <= c->size[1])
	{
		x = -1;
		while (++x <= c->size[0])
		{
			if (c->map[y][x] == '0')
				drawsquare(c, x, y, 0x00FFFFFF);
			else if (c->map[y][x] == '1')
				drawsquare(c, x, y, 0x00000000);
		}
	}
	drawanglepoint(c);
	drawplayer(c);
}
