/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:47:11 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/04/07 02:58:08 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	init(cubo *c)
{
	c->vars.mlx = mlx_init();
	c->vars.win = mlx_new_window(c->vars.mlx, TILESIZE * c->size[0] , TILESIZE * c->size[1], "Cub3d");
	c->vars.img = mlx_new_image(c->vars.mlx, TILESIZE * c->size[0], TILESIZE * c->size[1]);
	c->vars.addr = mlx_get_data_addr(c->vars.img, &c->vars.bits_per_pixel,
			&c->vars.line_length, &c->vars.endian);
	mlx_key_hook(c->vars.win, key_hook , c);
	// mlx_mouse_hook(minirt->vars->win, mouse_hook, minirt);
	mlx_hook(c->vars.win, 17, 0, bye, &(c->vars));
}

int	main(int argc, char **argv)
{
	cubo	*cubo;

	if (argc == 2)
		cubo = parser(argv[1]);
	init(cubo);
	//draw one pixel
	drawmap(cubo);
	mlx_loop(cubo->vars.mlx);
	freeall(cubo, cubo->lines);
	return (0);
}
