/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:12:22 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/13 16:08:50 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

void	ft_drawwalls(t_cub *cub, int beginx, int beginy, int lineH)
{
	int		x;
	int		y;
	size_t	tmp_x;
	size_t	tmp_y;

	x = beginx;
	while (x < beginx + 4)
	{
		y = beginy - lineH;
		if (y < 0)
			y = 0;
		if (y > 1080)
			y = 1080;
		while (y < beginy + lineH && y < 1080)
		{
			tmp_x = ((double)((double)(cub->data.ratiox / 32)) \
				*cub->texture[cub->data.dir].Widt);
			tmp_y = (((double)1 + ((double)(y - beginy - lineH) / \
					(double)(2 * lineH))) * \
						cub->texture[cub->data.dir].Heig);
			cub->image[0].arr[y++][x] = \
					cub->texture[cub->data.dir].arr[tmp_y][tmp_x];
		}
		x++;
	}
}

void	ft_putplayer(uint32_t **img_color, t_pos *pos)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			if (y >= pos->y / 2 - 2 && y <= pos->y / 2 + 2 && x \
					>= pos->x / 2 - 2 && x <= pos->x / 2 + 2)
				img_color[y][x++] = 0xff0000;
			else
				x++;
		}
		++y;
	}
}

void	ft_drawsquare(uint32_t **img_color, int posx, int posy, int scale)
{
	int	x;
	int	y;

	x = posx;
	y = posy;
	while (y < 1080)
	{
		x = posx;
		while (x < 1920)
		{
			if (y <= posy + scale && x <= posx + scale)
				img_color[y][x++] = 0xF3F3F2;
			else
				img_color[y][x++] = 0xFF000000;
		}
		++y;
	}
}

void	ft_drawmap(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	y = 0;
	while (y < cub->mapH)
	{
		x = 0;
		while (x < cub->mapW)
		{
			cub->data.xo = x * cub->mapScale / 2;
			cub->data.yo = y * cub->mapScale / 2;
			if (cub->map[y * cub->mapW + x] == 1)
				ft_drawsquare(cub->image[1].arr, cub->data.xo, \
						cub->data.yo, 32);
			x++;
		}
		y++;
	}
}

void	ft_draw_font(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			if (y >= 540)
				cub->image[2].arr[y][x++] = cub->pars->floor_color;
			else
				cub->image[2].arr[y][x++] = cub->pars->ceil_color;
		}
		++y;
	}
}
