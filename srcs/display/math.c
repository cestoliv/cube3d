/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcuminal <rcuminal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:20:23 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/20 19:23:55 by rcuminal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x \
			* (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_line(t_cub *cub, t_pos pos, int endx, int endy)
{
	float	deltax;
	float	deltay;
	float	pixelx;
	float	pixely;
	int		pixels;

	pixelx = pos.x / cub->resizemap;
	pixely = pos.y / cub->resizemap;
	deltax = endx - pixelx;
	deltay = endy - pixely;
	pixels = sqrt((deltax * deltax)
			+ (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = pos.x / cub->resizemap;
	pixely = pos.y / cub->resizemap;
	while (pixels)
	{
		my_mlx_pixel_put(&cub->image[0], pixelx, pixely, 0xff0000);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
	return ;
}

void	ft_setmovevalue(t_cub *cub)
{
	cub->pos.xo = 0;
	cub->pos.yo = 0;
	if (cub->pos.pdx < 0)
		cub->pos.xo -= 20;
	else
		cub->pos.xo = 20;
	if (cub->pos.pdy < 0)
		cub->pos.yo -= 20;
	else
		cub->pos.yo = 20;
	cub->pos.ipx = cub->pos.x / 64.0;
	cub->pos.ipx_add_xo = (cub->pos.x + cub->pos.xo) / 64.0;
	cub->pos.ipx_sub_xo = (cub->pos.x - cub->pos.xo) / 64.0;
	cub->pos.ipy = cub->pos.y / 64.0;
	cub->pos.ipy_add_yo = (cub->pos.y + cub->pos.yo) / 64.0;
	cub->pos.ipy_sub_yo = (cub->pos.y - cub->pos.yo) / 64.0;
	cub->pos.px = cos(cub->pos.pa + PI / 2) * 5;
	cub->pos.py = sin(cub->pos.pa + PI / 2) * 5;
	cub->pos.ipx_add_px = (cub->pos.x + cub->pos.px) / 64.0;
	cub->pos.ipx_sub_px = (cub->pos.x - cub->pos.px) / 64.0;
	cub->pos.ipy_add_py = (cub->pos.y + cub->pos.py) / 64.0;
	cub->pos.ipy_sub_py = (cub->pos.y - cub->pos.py) / 64.0;
}

void	ft_doormanager(t_cub *cub)
{
	if (cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_add_xo] == 2)
	{
		if (cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_add_xo] == 2)
			cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_add_xo] = 3;
		if (cub->map[cub->pos.ipy_add_yo * cub->mapw + cub->pos.ipx] == 2)
			cub->map[cub->pos.ipy_add_yo * cub->mapw + cub->pos.ipx] = 3;
	}
	else if (cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_add_xo] == 3)
	{
		if (cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_add_xo] == 3)
			cub->map[cub->pos.ipy * cub->mapw + cub->pos.ipx_add_xo] = 2;
		if (cub->map[cub->pos.ipy_add_yo * cub->mapw + cub->pos.ipx] == 3)
			cub->map[cub->pos.ipy_add_yo * cub->mapw + cub->pos.ipx] = 2;
	}
	cub->clavier[6] = 0;
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
