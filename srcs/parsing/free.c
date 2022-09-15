/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:08:49 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/15 18:03:46 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	free_map2d(t_map2D *map2d)
{
	size_t	cur;

	cur = 0;
	while (cur < map2d->height)
		free(map2d->map[cur++]);
	free(map2d->map);
	free(map2d);
	return (0);
}

void	*free_parsed(t_parsed *map)
{
	if (map->north_texture)
		free(map->north_texture);
	if (map->south_texture)
		free(map->south_texture);
	if (map->east_texture)
		free(map->east_texture);
	if (map->west_texture)
		free(map->west_texture);
	free_map2d(map->map2d);
	if (map->map1d->map)
		free(map->map1d->map);
	free(map->map1d);
	free(map);
	return (NULL);
}

void	*free_parsing_el(t_parsed *map, char **str1, char **str2, int fd)
{
	free(*str1);
	free(*str2);
	free(get_next_line(fd, GNL_CLEAR));
	return (free_parsed(map));
}

void	free_rgb(char *rgb_line, char **rgb)
{
	free(rgb_line);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
}
