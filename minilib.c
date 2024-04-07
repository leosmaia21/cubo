/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 02:45:34 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/04/07 05:02:04 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#define LEFT 65361
#define RIGHT 65363

int	bye(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

void updateangle(cubo *c, int keycode)
{
	if (keycode == RIGHT)
	{
		c->angle += 0.1;
		if (c->angle > 2 * PI)
			c->angle -= 2 * PI;
		c->pdx = cos(c->angle) * 8;
		c->pdy = sin(c->angle) * 8;
	}
	if (keycode == LEFT)
	{
		c->angle -= 0.1;
		if (c->angle < 0)
			c->angle += 2 * PI;
		c->pdx = cos(c->angle) * 8;
		c->pdy = sin(c->angle) * 8;
	}
}
int	key_hook(int keycode, cubo *c)
{
	if (keycode == 65307)
		bye(&c->vars);
	else if (keycode == 65362)
	{
		c->playerp[0] += c->pdx;
		c->playerp[1] += c->pdy;
	}
	else if (keycode == 65364)
	{
		c->playerp[0] -= c->pdx;
		c->playerp[1] -= c->pdy;
	}
	else
		updateangle(c, keycode);
	printf("keycode: %d\n", keycode);
	drawmap(c);
	return (0);
}