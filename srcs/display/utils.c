/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcuminal <rcuminal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:46:07 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/20 19:43:39 by rcuminal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

u_int32_t	**ft_mem2array(uint32_t *mem, size_t len_x, size_t len_y)
{
	u_int32_t	**arr;
	size_t		i;

	arr = malloc(len_y * sizeof(u_int32_t *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len_y)
	{
		arr[i] = &(mem[i * len_x]);
		++i;
	}
	return (arr);
}

void	init_imagespartfour(t_cub *cub, int *i)
{
	cub->texture[4].img = mlx_xpm_file_to_image(cub->mlx, \
	"./maps/assets/DOOR_1F.xpm", &cub->texture[4].widt, &cub->texture[4].heig);
	if (!cub->texture[4].img)
		return ;
	*i += 1;
	cub->texture[4].addr = mlx_get_data_addr(cub->texture[4].img, \
		&cub->texture[4].bits_per_pixel, &cub->texture[4].line_length,
			&cub->texture[4].endian);
	cub->texture[4].arr = ft_mem2array((uint32_t *)cub->texture[4].addr, \
		cub->texture[4].widt, cub->texture[4].heig);
}

void	init_imagesparthree(t_cub *cub, int *i)
{
	cub->texture[2].img = mlx_xpm_file_to_image(cub->mlx, \
	cub->pars->east_texture, &cub->texture[2].widt, &cub->texture[2].heig);
	if (!cub->texture[2].img)
		return ;
	*i += 1;
	cub->texture[2].addr = mlx_get_data_addr(cub->texture[2].img, \
		&cub->texture[2].bits_per_pixel, &cub->texture[2].line_length,
			&cub->texture[2].endian);
	cub->texture[2].arr = ft_mem2array((uint32_t *)cub->texture[2].addr, \
		cub->texture[2].widt, cub->texture[2].heig);
	cub->texture[3].img = mlx_xpm_file_to_image(cub->mlx, \
		cub->pars->west_texture, &cub->texture[3].widt, &cub->texture[3].heig);
	if (!cub->texture[3].img)
		return ;
	*i += 1;
	cub->texture[3].addr = mlx_get_data_addr(cub->texture[3].img, \
		&cub->texture[3].bits_per_pixel, &cub->texture[3].line_length,
			&cub->texture[3].endian);
	cub->texture[3].arr = ft_mem2array((uint32_t *)cub->texture[3].addr, \
		cub->texture[3].widt, cub->texture[3].heig);
	init_imagespartfour(cub, i);
}

void	init_imagesparttwo(t_cub *cub, int *i)
{
	*i += 1;
	cub->image[2].arr = ft_mem2array((uint32_t *)cub->image[2].addr, \
		1920, 1080);
	cub->texture[0].img = mlx_xpm_file_to_image(cub->mlx, \
		cub->pars->north_texture, &cub->texture[0].widt, &cub->texture[0].heig);
	if (!cub->texture[0].img)
		return ;
	*i += 1;
	cub->texture[0].addr = mlx_get_data_addr(cub->texture[0].img, \
		&cub->texture[0].bits_per_pixel, &cub->texture[0].line_length,
			&cub->texture[0].endian);
	cub->texture[0].arr = ft_mem2array((uint32_t *)cub->texture[0].addr, \
		cub->texture[0].widt, cub->texture[0].heig);
	cub->texture[1].img = mlx_xpm_file_to_image(cub->mlx, \
		cub->pars->south_texture, &cub->texture[1].widt, &cub->texture[1].heig);
	if (!cub->texture[1].img)
		return ;
	cub->texture[1].addr = mlx_get_data_addr(cub->texture[1].img, \
		&cub->texture[1].bits_per_pixel, &cub->texture[1].line_length,
			&cub->texture[1].endian);
	*i += 1;
	cub->texture[1].arr = ft_mem2array((uint32_t *) cub->texture[1].addr, \
		cub->texture[1].widt, cub->texture[1].heig);
	init_imagesparthree(cub, i);
}

void	init_imagespartone(t_cub *cub, int *i)
{
	cub->image[0].img = mlx_new_image(cub->mlx, 1920, 1080);
	if (!cub->image[0].img)
		return ;
	*i += 1;
	cub->image[0].addr = mlx_get_data_addr(cub->image[0].img, \
		&cub->image[0].bits_per_pixel, &cub->image[0].line_length,
			&cub->image[0].endian);
	cub->image[0].arr = ft_mem2array((uint32_t *)cub->image[0].addr, \
		1920, 1080);
	cub->image[1].img = mlx_new_image(cub->mlx, 1920, 1080);
	if (!cub->image[1].img)
		return ;
	*i += 1;
	cub->image[1].addr = mlx_get_data_addr(cub->image[1].img, \
		&cub->image[1].bits_per_pixel, &cub->image[1].line_length,
			&cub->image[1].endian);
	cub->image[1].arr = ft_mem2array((uint32_t *)cub->image[1].addr, \
		1920, 1080);
	cub->image[2].img = mlx_new_image(cub->mlx, 1920, 1080);
	if (!cub->image[2].img)
		return ;
	cub->image[2].addr = mlx_get_data_addr(cub->image[2].img, \
	&cub->image[2].bits_per_pixel, &cub->image[2].line_length, \
	&cub->image[2].endian);
	init_imagesparttwo(cub, i);
}
