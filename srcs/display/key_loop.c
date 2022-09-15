/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:35:03 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/15 15:49:37 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

void	ft_keyvalidation(t_cub *cub)
{
	int xo = 0;										//normer ce merdier et integrer aux structs
 	int yo = 0;

	if(cub->pos.pdx < 0)
		xo -= 20;
	else
		xo = 20;                                //x offset to check map
	if(cub->pos.pdy < 0)
		yo -= 20;
	else
		yo = 20;                                  //y offset to check map
 	int ipx=cub->pos.x/64.0, ipx_add_xo=(cub->pos.x+xo)/64.0, ipx_sub_xo=(cub->pos.x-xo) / 64.0;             //x position and offset
 	int ipy=cub->pos.y/64.0, ipy_add_yo=(cub->pos.y+yo)/64.0, ipy_sub_yo=(cub->pos.y-yo) / 64.0;
	if (cub->clavier[0] == 1)
	{
		if (cub->map[ipy * cub->mapW + ipx_add_xo] == 0)
			cub->pos.x += cub->pos.pdx;
		if (cub->map[ipy_add_yo * cub->mapW + ipx] == 0)
			cub->pos.y += cub->pos.pdy;
	}
	if (cub->clavier[1] == 1)
	{
		cub->pos.pa += 0.017;
		if (cub->pos.pa > 2 * PI)
			cub->pos.pa -= 2 * PI;
		cub->pos.pdx = cos(cub->pos.pa) * 5;
		cub->pos.pdy = sin(cub->pos.pa) * 5;
	}
	if (cub->clavier[2] == 1)
	{
		if (cub->map[ipy * cub->mapW + ipx_sub_xo] == 0)
			cub->pos.x -= cub->pos.pdx;
		if (cub->map[ipy_sub_yo * cub->mapW + ipx] == 0)
			cub->pos.y -= cub->pos.pdy;
	}
	if (cub->clavier[3] == 1)
	{
		cub->pos.pa -= 0.017;
		if (cub->pos.pa < 0)
			cub->pos.pa += 2 * PI;
		cub->pos.pdx = cos(cub->pos.pa) * 5;
		cub->pos.pdy = sin(cub->pos.pa) * 5;
	}
}

int	key_hook_release(int keycode, t_cub *cub)
{
	if (keycode == 13)
		cub->clavier[0] = 0;
	if (keycode == 2)
		cub->clavier[1] = 0;
	if (keycode == 1)
		cub->clavier[2] = 0;
	if (keycode == 0)
		cub->clavier[3] = 0;
	return (0);
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == 53)
		destroy(cub);
	if (keycode == 13)
		cub->clavier[0] = 1;
	if (keycode == 2)
		cub->clavier[1] = 1;
	if (keycode == 1)
		cub->clavier[2] = 1;
	if (keycode == 0)
		cub->clavier[3] = 1;
	return (0);
}

int	render_next_frame(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	ft_keyvalidation(cub);
	mlx_clear_window(cub->mlx, cub->mlxwin);
	drawrays(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlxwin, cub->image[2].img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->mlxwin, cub->image[0].img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->mlxwin, cub->image[1].img, 0, 0);
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
			cub->image[0].arr[y][x++] = 0xff000000;
		++y;
	}
	return (0);
}
