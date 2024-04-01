/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:04:09 by ledos-sa          #+#    #+#             */
/*   Updated: 2024/04/01 22:18:56 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

#include "42/libft/libft.h"
#include "42/get_next_line/get_next_line.h"
#include <unistd.h>
#include <stdio.h>

typedef struct
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	int map[8192][8192];
	int F[3];
	int C[3];
}	cubo;
cubo	*parser(char *name);

#endif
