/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:46:07 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/13 15:12:09 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

// void	ft_freetabb(u_int32_t**tab) // inutile pour l instant
// {
// 	int	i;

// 	i = 0;
// 	while (i < 1080)
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }

// void	ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*z;
// 	size_t			i;

// 	z = (unsigned char *)s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		z[i] = 0;
// 		i++;
// 	}
// }

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

void	init_imagesparttwo(t_cub *cub)
{
	cub->texture[1].img = mlx_xpm_file_to_image(cub->mlx, \
		cub->pars->south_texture, &cub->texture[1].Widt, &cub->texture[1].Heig);
	cub->texture[1].addr = mlx_get_data_addr(cub->texture[1].img, \
		&cub->texture[1].bits_per_pixel, &cub->texture[1].line_length,
			&cub->texture[1].endian);
	cub->texture[1].arr = ft_mem2array((uint32_t *) cub->texture[1].addr, \
		cub->texture[1].Widt, cub->texture[1].Heig);
	cub->texture[2].img = mlx_xpm_file_to_image(cub->mlx, cub->pars->east_texture, \
		&cub->texture[2].Widt, &cub->texture[2].Heig);
	cub->texture[2].addr = mlx_get_data_addr(cub->texture[2].img, \
		&cub->texture[2].bits_per_pixel, &cub->texture[2].line_length,
			&cub->texture[2].endian);
	cub->texture[2].arr = ft_mem2array((uint32_t *)cub->texture[2].addr, \
		cub->texture[2].Widt, cub->texture[2].Heig);
	cub->texture[3].img = mlx_xpm_file_to_image(cub->mlx,cub->pars->west_texture, \
		&cub->texture[3].Widt, &cub->texture[3].Heig);
	cub->texture[3].addr = mlx_get_data_addr(cub->texture[3].img, \
		&cub->texture[3].bits_per_pixel, &cub->texture[3].line_length,
			&cub->texture[3].endian);
	cub->texture[3].arr = ft_mem2array((uint32_t *)cub->texture[3].addr, \
		cub->texture[3].Widt, cub->texture[3].Heig);
}

void	init_imagespartone(t_cub *cub)
{
	cub->image[0].addr = mlx_get_data_addr(cub->image[0].img, \
		&cub->image[0].bits_per_pixel, &cub->image[0].line_length,
			&cub->image[0].endian);
	cub->image[0].arr = ft_mem2array((uint32_t *)cub->image[0].addr, \
		1920, 1080);
	cub->image[1].addr = mlx_get_data_addr(cub->image[1].img, \
		&cub->image[1].bits_per_pixel, &cub->image[1].line_length,
			&cub->image[1].endian);
	cub->image[1].arr = ft_mem2array((uint32_t *)cub->image[1].addr, \
		1920, 1080);
	cub->image[2].addr = mlx_get_data_addr(cub->image[2].img, \
		&cub->image[2].bits_per_pixel, &cub->image[2].line_length,
			&cub->image[2].endian);
	cub->image[2].arr = ft_mem2array((uint32_t *)cub->image[2].addr, \
		1920, 1080);
	cub->texture[0].img = mlx_xpm_file_to_image(cub->mlx, cub->pars->north_texture, \
		&cub->texture[0].Widt, &cub->texture[0].Heig);
	cub->texture[0].addr = mlx_get_data_addr(cub->texture[0].img, \
		&cub->texture[0].bits_per_pixel, &cub->texture[0].line_length,
			&cub->texture[0].endian);
	cub->texture[0].arr = ft_mem2array((uint32_t *)cub->texture[0].addr, \
		cub->texture[0].Widt, cub->texture[0].Heig);
	init_imagesparttwo(cub);
}
