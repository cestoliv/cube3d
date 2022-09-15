/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:26:24 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/15 18:36:17 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

#include "parsing.h"

void	init_parsed_struct(t_parsed **result)
{
	*result = malloc(sizeof(t_parsed));
	(*result)->north_texture = NULL;
	(*result)->south_texture = NULL;
	(*result)->east_texture = NULL;
	(*result)->west_texture = NULL;
	(*result)->floor_color = -1;
	(*result)->ceil_color = -1;
	(*result)->map2d = malloc(sizeof(t_map2D));
	(*result)->map2d->map = NULL;
	(*result)->map2d->width = 0;
	(*result)->map2d->height = 0;
	(*result)->map1d = malloc(sizeof(t_map1D));
	(*result)->map1d->map = NULL;
	(*result)->map1d->width = 0;
	(*result)->map1d->height = 0;
}

int	has_every_data(t_parsed *map)
{
	int	count;

	count = 0;
	if (map->north_texture)
		count++;
	if (map->south_texture)
		count++;
	if (map->east_texture)
		count++;
	if (map->west_texture)
		count++;
	if (map->floor_color != -1)
		count++;
	if (map->ceil_color != -1)
		count++;
	if (count == 6)
		return (1);
	return (0);
}

int	check_map_line_char(char *line)
{
	size_t	cur;

	cur = 0;
	while (line[cur] && line[cur] != '\n')
	{
		if (!ft_str_contains(" 10NSEW", line[cur]))
			return (0);
		cur++;
	}
	return (1);
}

void	create_map1d(t_parsed *map)
{
	int	x;
	int	y;
	int	cur;

	map->map1d->width = map->map2d->width;
	map->map1d->height = map->map2d->height;
	map->map1d->map = malloc(sizeof(int)
			* (map->map1d->width * map->map1d->height));
	y = 0;
	cur = 0;
	while (map->map2d->map[y])
	{
		x = 0;
		while (map->map2d->map[y][x])
		{
			if (ft_str_contains("0NSEW", map->map2d->map[y][x]))
				map->map1d->map[cur] = 0;
			else
				map->map1d->map[cur] = 1;
			cur++;
			x++;
		}
		y++;
	}
}

t_parsed	*parse(char *file_path)
{
	t_parsed	*result;
	char		*map_line;

	init_parsed_struct(&result);
	map_line = parse_map_file(file_path, result);
	if (!map_line)
		return (0);
	result->map2d->map = parse_map_line(map_line);
	result->map2d->height = get_map_height(result->map2d->map);
	result->map2d->width = get_map_width(result->map2d->map);
	free(map_line);
	if (!check_map(result))
		return (free_parsed(result));
	create_map1d(result);
	get_player(result->map2d->map, &(result->player));
	return (result);
}
