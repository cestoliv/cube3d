/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:20:23 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/12 15:10:36 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

float degToRad(int a)
{
	return a*M_PI/180.0;
}

float	dist(float ax, float ay, float bx, float by, float ang)
{
	return (   sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)));	
}

float FixAng(float a)
{
	if(a>359)
		a-=360;
	if(a<0)
		a+=360;
	return a;
}

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_line(t_image *data, int beginx, int beginy, int endx, int endy, int color)
{
	float	deltax;
	float	deltay;
	float	pixelx;
	float	pixely;
	int		pixels;



	pixelx = beginx;
	pixely = beginy;
	deltax = endx - beginx;
	deltay = endy - beginy ;
	pixels = sqrt((deltax * deltax)
			+ (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = beginx;
	pixely = beginy;
	// if (pixelx > 1000)
	// 	pixelx = 1000;
	// if (pixely > 1000)
	// 	pixely = 1000;
	
	while (pixels) //&& pixelx > 0 && pixely > 0 && pixelx < 1000 && pixely < 1000
	{
		if (color == 2)
			my_mlx_pixel_put(data, pixelx, pixely, 0xff0000);
		else if (color == 1)
			my_mlx_pixel_put(data, pixelx, pixely, 0xfffe00);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
	return ;
}
