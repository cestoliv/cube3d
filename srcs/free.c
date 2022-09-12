/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:08:49 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/12 10:13:06 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	free_map2D(t_map2D *map2D)
{
	size_t	cur;

	cur = 0;
	while (cur < map2D->height)
		free(map2D->map[cur++]);
	free(map2D->map);
	free(map2D);
	return (0);
}

void	*free_parsed(t_parsed *map)
{
	size_t	cur;

	if (map->north_texture)
		free(map->north_texture);
	if (map->south_texture)
		free(map->south_texture);
	if (map->east_texture)
		free(map->east_texture);
	if (map->west_texture)
		free(map->west_texture);
	if (map->floor_color)
		free(map->floor_color);
	if (map->ceil_color)
		free(map->ceil_color);
	free_map2D(map->map2D);
	free(map);
	return (NULL);
}

void	*free_parsing_elems(t_parsed *map, char **str1, char **str2, int fd, char *error)
{
	ft_printf("%s", error);
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
