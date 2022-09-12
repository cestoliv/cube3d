/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:30:42 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/12 10:31:21 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	get_map_line_height(char *line)
{
	size_t	cur;
	size_t	height;

	cur = 0;
	height = 0;
	while (line[cur])
	{
		if (line[cur] == '\n')
			height++;
		cur++;
	}
	return (height);
}

size_t	get_map_line_width(char *line)
{
	size_t	cur;
	size_t	current_width;
	size_t	max_width;

	cur = 0;
	current_width = 0;
	max_width = 0;
	while (line[cur])
	{
		if (line[cur] == '\n')
		{
			if (current_width > max_width)
				max_width = current_width;
			current_width = 0;
		}
		else
			current_width++;
		cur++;
	}
	return (max_width);
}

char	**alloc_map(char *map_line)
{
	char	**map;
	size_t	height;
	size_t	width;
	size_t	cur;

	height = get_map_line_height(map_line);
	width = get_map_line_width(map_line);
	map = malloc(sizeof(char *) * (height + 1));
	cur = 0;
	while (cur < height)
	{
		map[cur] = malloc(sizeof(char) * (width + 1));
		ft_memset(map[cur], ' ', width);
		map[cur][width] = 0;
		cur++;
	}
	map[cur] = NULL;
	return (map);
}

char	**parse_map_line(char *map_line)
{
	char	**map;
	size_t	cur;
	size_t	previous_cur;
	size_t	y_cur;

	cur = 0;
	previous_cur = 0;
	y_cur = 0;
	map = alloc_map(map_line);
	while (map_line[cur])
	{
		if (map_line[cur] == '\n')
		{
			ft_strlcpy2(map[y_cur++], map_line + previous_cur, cur - previous_cur + 1);
			previous_cur = cur + 1;
		}
		cur++;
	}
	return (map);
}
