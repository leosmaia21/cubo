/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:04:09 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/05/01 00:40:35 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

#include <math.h>
#include <limits.h>
#include "42/libft/libft.h"
#include "minilib/mlx.h"
#include "42/get_next_line/get_next_line.h"
#include <unistd.h>
#include <stdio.h>


#define PI 3.141592653
#define SIZE 820
#define TILE 64
#define PLAYERSIZE 15
#define SLIDE 7
#define VIEWANGLE (3.141592653/4)
#define HORIZONTAL 0
#define VERTICAL 1
#define ANGLEVIEW (PI/4)
#define ANGLEITER 800

typedef struct s_vars {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_vars;

typedef struct point
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}				t_point2;

typedef struct
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char 	map[SIZE][SIZE];
	int		F[3];
	int		C[3];
	int		size[2];
	int		player[2];
	int		pdx;
	int		pdy;
	double	angle;
	t_vars	vars;
	t_list	*lines;
	int		playerp[2];
	int		tilesize[2];
	double	ra;
	int		xn;
	int		yn;
	int		xs;
	int		ys;
	int		vertx;
	int		verty;
	int		horx;
	int		hory;
	double	distV;
	double	distH;
	int		distT;
}	cubo;

cubo	*parser(char *name);
void	drawmap(cubo *c);
void	drawsquare(cubo *c, int x, int y, int color);
void	drawplayer(cubo *c);
void	freeall(cubo *cubo, t_list *lines);
int		key_hook(int keycode, cubo *c);
int		bye(t_vars *vars);
void	my_mlx_pixel_put(t_vars *data, int x, int y, int color);

#endif
