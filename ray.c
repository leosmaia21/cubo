/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:34:08 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/05/01 19:26:23 by ledos-sa         ###   ########.fr       */
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
			my_mlx_pixel_put(&c->vars, x * TILE + xx, y * TILE + yy, color);
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
			my_mlx_pixel_put(&c->vars, c->playerp[1] + xx, c->playerp[0] + yy, 0x00FF0000);
		}
	}
}

int	checkinside(cubo *c, int x, int y, int direction)
{
	if (x < 0 || y < 0 || x > c->size[0] * TILE || y > c->size[1] * TILE)
		return (0);
	if (c->map[y / TILE][x / TILE] == '1')
	{
		if (direction == HORIZONTAL)
		{
			c->horx = x;
			c->hory = y;
		}
		else
		{
			c->vertx = x;
			c->verty = y;
		}
		return (1);
	}
	return (0);
}

//TODO check angle 0 and PI
int	drawhorizontal(cubo *c)
{
	int	dot;

	if (c->ra != 0.0 && c->ra != PI)
	{
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
			if (checkinside(c, c->playerp[1] + c->xn, c->playerp[0] + c->yn, HORIZONTAL))
				return (1);
			c->xn += c->xs;
			c->yn += c->ys;
		}
	}
	return (0);
}

int	drawvertical(cubo *c)
{
	int	dot;

	if (c->ra != PI / 2 && c->ra != 3 * PI / 2)
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
			if (checkinside(c, c->playerp[1] + c->xn, c->playerp[0] + c->yn, VERTICAL))
				return (1);
			c->xn += c->xs;
			c->yn += c->ys;
		}
	}
	return (0);
}

int	dist(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void drawline(cubo *c, float x0, float y0, const float x1, const float y1)
{
    float x = x1 - x0;
    float y = y1 - y0;
    const float max = fmaxf(fabsf(x), fabsf(y));
    x /= max;
    y /= max;
    for (float n = 0; n < max; ++n)
    {
		my_mlx_pixel_put(&c->vars, x0, y0, 0x00FF0000);
        x0 += x;
        y0 += y;
    }
}

void drawline2(cubo *c, t_point2 p, int width)
{
	float	x;
	float	y;
	float	max;
	int 	n;
	int		i;

	x = p.x2 - p.x1;
	y = p.y2 - p.y1;
	max = fmaxf(fabsf(x), fabsf(y));
	x /= max;
	y /= max;
	i = -1;
	while (++i < width)
	{
		n = -1;
		while (++n < max)
		{
			my_mlx_pixel_put(&c->vars, p.x1, p.y1, 0x00FF0000);
			p.x1 += x;
			p.y1 += y;
		}
		p.x1 = p.x1 - (max * x);
		p.y1 = p.y1 - (max * y);
		p.x1++;
	}
}


void	resetvalues(cubo *c)
{
	c->horx = 0;
	c->hory = 0;
	c->vertx = 0;
	c->verty = 0;
	c->distH = 0;
	c->distV = 0;
	c->xn = 0;
	c->yn = 0;
	c->xs = 0;
	c->ys = 0;
}

void drawcleanmap(cubo *c)
{
	int	x;
	int	y;

	y = -1;
	while (++y < c->size[1] * TILE)
	{
		x = -1;
		while (++x < c->size[0] * TILE + 300)
		{
			my_mlx_pixel_put(&c->vars, x, y, 0x00000000);
		}
	}
		x = c->size[0] * TILE - 1;
}

void drawrays(cubo *c)
{
	int	x;
	int	ret[2];
	float lineH;
	float lineO;

	x = -1;
	resetvalues(c);
	c->ra = c->angle - 0.0001 - ANGLEVIEW / 2;
	// printf("ola\n");

	while (++x < ANGLEITER)
	{
		ret[0] = drawhorizontal(c);
		ret[1] = drawvertical(c);
		c->distH = dist(c->playerp[1], c->playerp[0], c->horx, c->hory);
		c->distV = dist(c->playerp[1], c->playerp[0], c->vertx, c->verty);
		if (c->distH < c->distV && ret[0] == 1)
		{
			drawline(c, c->playerp[1], c->playerp[0], c->horx, c->hory);
			c->distT = c->distH;
		}
		else if (ret[1] == 1)
		{
			drawline(c, c->playerp[1], c->playerp[0], c->vertx, c->verty);
			c->distT = c->distV;
		}
		lineH = (300.0) / c->distT;
		if (lineH > 300)
			lineH = 300;
		lineO = 150 - (lineH / 2);
		int t = c->size[0] * TILE;
		drawline2(c, (t_point2){x * (300 / ANGLEITER) + t, lineO, x* (300 / ANGLEITER) + t, lineO + lineH}, 300/ANGLEITER);
		c->ra += ANGLEVIEW / ANGLEITER;
		if (c->ra > 2 * PI)
			c->ra -= 2 * PI;

	}
	mlx_put_image_to_window(c->vars.mlx, c->vars.win, c->vars.img, 0, 0);
}

void drawanglepoint(cubo *c)
{
	int x;
	int y;

	x = c->playerp[1] + c->pdx * 4;
	y = c->playerp[0] + c->pdy * 4;
	// mlx_pixel_put(c->vars.mlx, c->vars.win, x, y, 0x00FF0000);
}

void	drawmap(cubo *c)
{
	int	x;
	int	y;

	y = -1;
	drawcleanmap(c);
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
