/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcuminal <rcuminal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:35:03 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/19 23:13:04 by rcuminal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

void	ft_key_partone(t_cub *cub)
{
	if (cub->clavier[0] == 1)
	{
		if (cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_add_xo] == 0
			|| cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_add_xo] == 3)
			cub->pos.x += cub->pos.pdx;
		if (cub->map[cub->pos.ipy_add_yo * cub->mapw + cub->pos.ipx] == 0
			|| cub->map[cub->pos.ipy_add_yo * cub->mapw + cub->pos.ipx] == 3)
			cub->pos.y += cub->pos.pdy;
	}
	if (cub->clavier[1] == 1)
	{
		cub->pos.pa += 0.05;
		if (cub->pos.pa > 2 * PI)
			cub->pos.pa -= 2 * PI;
		cub->pos.pdx = cos(cub->pos.pa) * 5;
		cub->pos.pdy = sin(cub->pos.pa) * 5;
	}
}

void	ft_key_parttwo(t_cub *cub)
{
	if (cub->clavier[4] == 1)
	{
		if (cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_sub_px] == 0
			|| cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_sub_px] == 3)
			cub->pos.x -= cub->pos.px;
		if (cub->map[cub->pos.ipy_sub_py * cub->mapw + cub->pos.ipx] == 0
			|| cub->map[cub->pos.ipy_sub_py * cub->mapw + cub->pos.ipx] == 3)
			cub->pos.y -= cub->pos.py;
	}
	if (cub->clavier[5] == 1)
	{
		if (cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_add_px] == 0
			|| cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_add_px] == 3)
			cub->pos.x += cub->pos.px;
		if (cub->map[cub->pos.ipy_add_py * cub->mapw + cub->pos.ipx] == 0
			|| cub->map[cub->pos.ipy_add_py * cub->mapw + cub->pos.ipx] == 3)
			cub->pos.y += cub->pos.py;
	}
}

void	ft_keyvalidation(t_cub *cub)
{
	ft_setmovevalue(cub);
	ft_key_partone(cub);
	if (cub->clavier[2] == 1)
	{
		if (cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_sub_xo] == 0
			|| cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_sub_xo] == 3)
			cub->pos.x -= cub->pos.pdx;
		if (cub->map[cub->pos.ipy_sub_yo * cub->mapw + cub->pos.ipx] == 0
			|| cub->map[cub->pos.ipy_sub_yo * cub->mapw + cub->pos.ipx] == 3)
			cub->pos.y -= cub->pos.pdy;
	}
	if (cub->clavier[3] == 1)
	{
		cub->pos.pa -= 0.05;
		if (cub->pos.pa < 0)
			cub->pos.pa += 2 * PI;
		cub->pos.pdx = cos(cub->pos.pa) * 5;
		cub->pos.pdy = sin(cub->pos.pa) * 5;
	}
	ft_key_parttwo(cub);
	if (cub->clavier[6] == 1)
		ft_doormanager(cub);
}

int	key_hook_release(int keycode, t_cub *cub)
{
	if (keycode == 13)
		cub->clavier[0] = 0;
	if (keycode == 2)
		cub->clavier[5] = 0;
	if (keycode == 1)
		cub->clavier[2] = 0;
	if (keycode == 0)
		cub->clavier[4] = 0;
	if (keycode == 123)
		cub->clavier[3] = 0;
	if (keycode == 124)
		cub->clavier[1] = 0;
	return (0);
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == 53)
		destroy(cub);
	if (keycode == 13)
		cub->clavier[0] = 1;
	if (keycode == 2)
		cub->clavier[5] = 1;
	if (keycode == 1)
		cub->clavier[2] = 1;
	if (keycode == 0)
		cub->clavier[4] = 1;
	if (keycode == 123)
		cub->clavier[3] = 1;
	if (keycode == 124)
		cub->clavier[1] = 1;
	if (keycode == 3)
		cub->clavier[6] = 1;
	return (0);
}
