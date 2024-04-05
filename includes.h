/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:04:09 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/04/05 22:50:48 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

#include "42/libft/libft.h"
#include "42/get_next_line/get_next_line.h"
#include <unistd.h>
#include <stdio.h>

#define SIZE 1000
typedef struct
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char map[SIZE][SIZE];
	int F[3];
	int C[3];
	int size[2];
	int player[2];
}	cubo;
cubo	*parser(char *name);

#endif
