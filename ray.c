/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:34:08 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/04/25 20:57:56 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include <stdio.h>

void	drawsquare(cubo *c, int x, int y, int color)
{
	int	yy;
	int	xx;

	yy = -1;
	while (++yy < TILE)
	{
		xx = -1;
		while (++xx < TILE)
		{
			mlx_pixel_put(c->vars.mlx, c->vars.win, x * TILE + xx, y * TILE + yy, color);
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
			mlx_pixel_put(c->vars.mlx, c->vars.win, c->playerp[1] + xx, c->playerp[0] + yy, 0x00FF0000);
		}
	}
}

int	checkinside(cubo *c, int x, int y)
{
	// mlx_pixel_put(c->vars.mlx, c->vars.win, x, y, 0x000000FF);
	printf("x: %d, y: %d\n", x, y);
	if (c->map[y / TILE][x / TILE] == '1')
	{
		mlx_pixel_put(c->vars.mlx, c->vars.win, x, y, 0x0000FF00);
		return (1);
	}
	return (0);
}

int	drawhorizontal(cubo *c)
{
	int	x;
	int	dot;

	x = -1;
	c->ra = c->angle;
	while (++x < 1 && c->ra != 0.0 && c->ra != PI)
	{
		// horizontal
		if (c->ra > 0 && c->ra < PI)
		{
			c->yn = (c->playerp[0] / TILE) * TILE + TILE - c->playerp[0];
			c->ys = TILE;
		}
		else
		{
			c->yn = -(c->playerp[0] - ((c->playerp[0] / TILE) * TILE)) - 1;
			c->ys = -TILE;
		}
		c->xs = c->ys / tan(c->ra);
		c->xn = c->yn / tan(c->ra);
		dot = -1;
		while (++dot < 8)
		{
			if (checkinside(c, c->playerp[1] + c->xn, c->playerp[0] + c->yn))
				return (1);
			c->xn += c->xs;
			c->yn += c->ys;
		}
	}
	return (0);
}

int	drawvertical(cubo *c)
{
	int	x;
	int	dot;

	x = -1;
	c->ra = c->angle;
	while (++x < 1 && c->ra != PI / 2 && c->ra != 3 * PI / 2)
	{
		if (c->ra < PI / 2 || c->ra > 3 * PI / 2)
		{
			c->xn = (TILE + (c->playerp[1] / TILE) * TILE) - c->playerp[1];
			c->xs = TILE;
		}
		else
		{
			c->xn = -(c->playerp[1] - ((c->playerp[1] / TILE) * TILE)) - 1;
			c->xs = -TILE;
		}
		c->ys = c->xs * tan(c->ra);
		c->yn = c->xn * tan(c->ra);
		dot = -1;
		while (++dot < 8)
		{
			if (checkinside(c, c->playerp[1] + c->xn, c->playerp[0] + c->yn))
				return (1);
			c->xn += c->xs;
			c->yn += c->ys;
		}
	}
	return (0);
}

void drawrays(cubo *c)
{
	drawhorizontal(c);
	// mlx_pixel_put(c->vars.mlx, c->vars.win, c->playerp[1] + c->xs, c->playerp[0] + c->ys, 0x00FF0000);
}

void drawanglepoint(cubo *c)
{
	int x;
	int y;

	x = c->playerp[1] + c->pdx * 4;
	y = c->playerp[0] + c->pdy * 4;
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
	drawrays(c);
}
