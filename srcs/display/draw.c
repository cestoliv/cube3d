/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:12:22 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/12 15:10:32 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

void	ft_drawwalls(t_cub *cub, int beginx, int beginy, int lineH, float tx)                 // draw walls 4pix de large (tx, ty , ty_step inutilisable et pas compris)
{
	int x;
	int y;
	int color;
	x = beginx;
	
	while (x < beginx + 4)				
	{
		y = beginy - lineH;
		if (y < 0)
			y = 0;
		if (y > 1080)
			y = 1080;
		while ( y < beginy + lineH && y < 1080)
		{
			if (x > 0 && y > 0 && x < 1920 && y < 1080)
			{
				size_t tmp_x = ((double)((double)(tx / 32)) * cub->texture[cub->data.dir].Widt);										// partie adaptation texture to wall  // pas ouf mais "ok"
                size_t tmp_y = (((double)1 + ( (double)(y - beginy - lineH) / (double)(2 * lineH))) * cub->texture[cub->data.dir].Heig);
                cub->image[0].arr[y++][x] = cub->texture[cub->data.dir].arr[tmp_y ][tmp_x];
			}
			else
				y++;
			
		}
		x++;

	}
}

void ft_putplayer(uint32_t**	img_color, t_pos *pos) // petit carre avec direction grace a un point
{
	int x;
	int	y;

	x = 0;
	y = 0;
	while (y < 1080)
	{
		int x = 0;
		while (x < 1920)
		{
			if (y >= pos->y / 2 - 2 && y <= pos->y / 2 + 2 && x >= pos->x / 2 - 2 && x <= pos->x / 2 + 2)
				img_color[y][x++] = 0xff0000;
			else
				x++;
		}
		++y;
	}
}

void ft_drawsquare(uint32_t**	img_color, int posx, int posy, int scale, int color) // pour la map pr l instant
{
	int x;
	int	y;

	x = posx;
	y = posy;
	while (y < 1080)
	{
		x = posx;
		while (x < 1920)
		{
			if (y <= posy + scale   && x <= posx + scale)
				img_color[y][x++] = 0xF3F3F2;
			else
				img_color[y][x++] = 0xFF000000;
		}
		++y;
	}
}

void ft_drawmap(t_cub *cub)
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
			if(cub->map[ y * cub->mapW + x] == 1)
			{
				ft_drawsquare(cub->image[1].arr, cub->data.xo, cub->data.yo, 32, 0x858485);
			}
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
		//printf("prout\n");
//	uint32_t**	img_color = ft_mem2array((uint32_t*)cub->image[2].addr, 1920, 1080);
	while (y < 1080)
	{
		int x = 0;
		while (x < 1920)
		{
			if (y >= 540)
				cub->image[2].arr[y][x++] = 0x003300;
			else
				cub->image[2].arr[y][x++] = 0x000033;
		}
		++y;
	}
}