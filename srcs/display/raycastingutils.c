/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastingutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:17:48 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/13 14:59:16 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

void	ft_final_maths(t_cub *cub)
{
	cub->data.ca = cub->pos.pa - cub->data.ra;
	if (cub->data.ca < 0)
		cub->data.ca += 2 * PI;
	if (cub->data.ca > 2 * PI)
		cub->data.ca -= 2 * PI;
	cub->data.disT = cub->data.disT * cos(cub->data.ca) / 2;
	cub->data.lineH = (cub->mapScale * 340) / cub->data.disT;
	cub->data.lineO = 540;
	if (cub->data.shade == 1)
	{
		cub->data.ratiox = (int)(cub->data.rayX / 2.0) % 32;
		if (cub->data.ra > 180)
			cub->data.ratiox = 31 - cub->data.ratiox;
	}
	else
	{
		cub->data.ratiox = (int)(cub->data.rayY / 2.0) % 32;
		if (cub->data.ra > 90 && cub->data.ra < 270)
			cub->data.ratiox = 31 - cub->data.ratiox;
	}
}

void	reset_raycasting_varshori(t_cub *cub)
{
	cub->data.dow = 0;
	cub->data.disH = 1000000;
	cub->data.horix = cub->pos.x;
	cub->data.horiy = cub->pos.y;
	cub->data.aTan = -1 / tan(cub->data.ra);
}

void	reset_raycasting_varsverti(t_cub *cub)
{
	cub->data.dow = 0;
	cub->data.disV = 1000000;
	cub->data.vertx = cub->pos.x;
	cub->data.verty = cub->pos.y;
	cub->data.nTan = -tan(cub->data.ra);
}

void	fix_angle(t_cub *cub)
{
	if (cub->data.ra < 0)
		cub->data.ra += 2 * PI;
	if (cub->data.ra > 2 * PI)
		cub->data.ra -= 2 * PI;
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
