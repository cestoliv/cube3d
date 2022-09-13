/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastinghv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:57:56 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/13 14:59:11 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

void	ft_hori(t_cub *cub)
{
	{
		cub->data.rayY = (((int)cub->pos.y >> 6) << 6) - 0.0001;
		cub->data.rayX = (cub->pos.y - cub->data.rayY) \
			* cub->data.aTan + cub->pos.x;
		cub->data.yo = -64;
		cub->data.xo = -cub->data.yo * cub->data.aTan;
		cub->data.tmpdir1 = N;
	}
	if (cub->data.ra < PI)
	{
		cub->data.rayY = (((int)cub->pos.y >> 6) << 6) + 64;
		cub->data.rayX = (cub->pos.y - cub->data.rayY) \
			* cub->data.aTan + cub->pos.x;
		cub->data.yo = 64;
		cub->data.xo = -cub->data.yo * cub->data.aTan;
		cub->data.tmpdir1 = S;
	}
	if (cub->data.ra == 0 || cub->data.ra == PI)
	{
		cub->data.rayX = cub->pos.x;
		cub->data.rayY = cub->pos.y;
		cub->data.dow = cub->max;
	}
}

void	ft_hori_try_contact(t_cub *cub)
{
	while (cub->data.dow < cub->max)
	{
		cub->data.mx = (int)(cub->data.rayX) >> 6;
		cub->data.my = (int)(cub->data.rayY) >> 6;
		cub->data.mp = cub->data.my * cub->mapW + cub->data.mx;
		if (cub->data.mp > 0 && cub->data.mp < cub->mapW \
			* cub->mapH && cub->map[cub->data.mp] == 1)
		{
			cub->data.horix = cub->data.rayX;
			cub->data.horiy = cub->data.rayY;
			cub->data.disH = dist(cub->pos.x, cub->pos.y, \
				cub->data.horix, cub->data.horiy);
			cub->data.dow = cub->max;
		}
		else
		{
			cub->data.rayX += cub->data.xo;
			cub->data.rayY += cub->data.yo;
			cub->data.dow += 1;
		}
	}
}

void	ft_verti(t_cub *cub)
{
	if (cub->data.ra > PI2 && cub->data.ra < PI3)
	{
		cub->data.rayX = (((int)cub->pos.x >> 6) << 6) - 0.0001;
		cub->data.rayY = (cub->pos.x - cub->data.rayX) \
			* cub->data.nTan + cub->pos.y;
		cub->data.xo = -64;
		cub->data.yo = -cub->data.xo * cub->data.nTan;
		cub->data.tmpdir2 = O;
	}
	if (cub->data.ra < PI2 || cub->data.ra > PI3)
	{
		cub->data.rayX = (((int)cub->pos.x >> 6) << 6) + 64;
		cub->data.rayY = (cub->pos.x - cub->data.rayX) \
			* cub->data.nTan + cub->pos.y;
		cub->data.xo = 64;
		cub->data.yo = -cub->data.xo * cub->data.nTan;
		cub->data.tmpdir2 = E;
	}
	if (cub->data.ra == 0 || cub->data.ra == PI)
	{
		cub->data.rayX = cub->pos.x;
		cub->data.rayY = cub->pos.y;
		cub->data.dow = cub->max;
	}
}

void	ft_verti_try_contact(t_cub *cub)
{
	while (cub->data.dow < cub->max)
	{
		cub->data.mx = (int)(cub->data.rayX) >> 6;
		cub->data.my = (int)(cub->data.rayY) >> 6;
		cub->data.mp = cub->data.my * cub->mapW + cub->data.mx;
		if (cub->data.mp > 0 && cub->data.mp < cub->mapW \
			* cub->mapH && cub->map[cub->data.mp] == 1)
		{
			cub->data.vertx = cub->data.rayX;
			cub->data.verty = cub->data.rayY;
			cub->data.disV = dist(cub->pos.x, cub->pos.y, \
				cub->data.vertx, cub->data.verty);
			cub->data.dow = cub->max;
		}
		else
		{
			cub->data.rayX += cub->data.xo;
			cub->data.rayY += cub->data.yo;
			cub->data.dow += 1;
		}
	}
}

void	ft_shorter(t_cub *cub)
{
	if (cub->data.disV > cub->data.disH)
	{
		if (cub->data.tmpdir1 == N)
			cub->data.dir = N;
		else
			cub->data.dir = S;
		cub->data.rayX = cub->data.horix;
		cub->data.rayY = cub->data.horiy;
		cub->data.disT = cub->data.disH;
	}
	if (cub->data.disV < cub->data.disH)
	{
		if (cub->data.tmpdir2 == E)
			cub->data.dir = E;
		else
			cub->data.dir = O;
		cub->data.shade = 0.5;
		cub->data.rayX = cub->data.vertx;
		cub->data.rayY = cub->data.verty;
		cub->data.disT = cub->data.disV;
	}
}
