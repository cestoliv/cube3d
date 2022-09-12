/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:46:07 by rcuminal          #+#    #+#             */
/*   Updated: 2022/09/12 15:10:38 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "proto.h"

void	ft_freetabb(u_int32_t**tab) // inutile pour l instant
{
	int	i;

	i = 0;
	while (i < 1080)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*z;
	size_t			i;

	z = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		z[i] = 0;
		i++;
	}
}

u_int32_t**	ft_mem2array(uint32_t *mem, size_t len_x, size_t len_y)            // 1D to 2D
{
	u_int32_t	**arr;
	size_t		i;

	arr = malloc(len_y * sizeof(u_int32_t*));
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
