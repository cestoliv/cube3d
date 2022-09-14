/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Romain <Romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:20:23 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/13 18:25:58 by Romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
