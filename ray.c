/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:34:08 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/04/08 22:52:25 by ledos-sa         ###   ########.fr       */
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
			mlx_pixel_put(c->vars.mlx, c->vars.win, c->playerp[1] + xx, c->playerp[0] + yy, 0x00FF0000);
		}
	}
}

int	checkpointinside(cubo *c, int x, int y)
{
	printf("x: %d, y: %d\n", x, y);
	if (c->map[y / TILESIZE][x / TILESIZE] == '1')
		return (1);
	return (0);
}

void	drawhorizontal(cubo *c)
{
	int x;
	int	dot;

	x = -1;
	c->ra = c->angle;
	while (++x < 1)
	{
		// horizontal
		if (c->ra > 0 && c->ra < PI)
			c->yn = (c->playerp[0] / TILESIZE) * TILESIZE + TILESIZE - c->playerp[0];
		else
			c->yn = -(c->playerp[0] - ((c->playerp[0] / TILESIZE) * TILESIZE));
		c->xn = c->yn / tan(c->ra);
		c->ys = TILESIZE;
		c->xs = c->ys / tan(c->ra);
		if (checkpointinside(c, c->playerp[1] + c->xn, c->playerp[0] + c->yn) == 1)
			break ;
		dot = 0;
		while (dot < 8)
		{
			if (checkpointinside(c, c->playerp[1] + c->xn, c->playerp[0] + c->yn) == 1)
				break ;
			c->xn += c->xs;
			c->yn += c->ys;
			dot++;
		}
	}
}

void	drawvertical(cubo *c)
{
	int	x;
	int	dot;

	x = -1;

	c->ra = c->angle;
	while (++x < 1)
	{
		// vertical
		if (c->ra < PI / 2 || c->ra > 3 * PI / 2)
			c->xs = c->playerp[0] + (TILESIZE - c->playerp[0] % TILESIZE);
		else
			c->xs = c->playerp[0] - c->playerp[0] / TILESIZE * TILESIZE;
		c->ys = c->xs * tan(c->ra);
		c->yn = c->xn * tan(c->ra);
		if (checkpointinside(c, c->xs, c->ys) == 1)
			break ;
		dot = 0;
		while (dot < 8)
		{
			if (checkpointinside(c, c->xs, c->ys) == 1)
				break ;
			c->xs += c->xn;
			c->ys += c->yn;
			dot++;
		}
	}
}

void drawrays(cubo *c)
{
	drawhorizontal(c);
	mlx_pixel_put(c->vars.mlx, c->vars.win, c->playerp[1] + c->xs, c->playerp[0] + c->ys, 0x00FF0000);
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
