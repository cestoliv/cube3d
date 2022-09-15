/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:37:13 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/15 17:27:19 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	get_map_height(char **map)
{
	size_t	cur;

	cur = 0;
	while (map[cur])
		cur++;
	return (cur);
}

size_t	get_map_width(char **map)
{
	if (map[0])
		return (ft_strlen(map[0]));
	return (0);
}

int	get_player(char **map, t_player *player)
{
	size_t	x_cur;
	size_t	y_cur;
	int		count;

	y_cur = 0;
	count = 0;
	while (map[y_cur])
	{
		x_cur = 0;
		while (map[y_cur][x_cur])
		{
			if (map[y_cur][x_cur] == 'N' || map[y_cur][x_cur] == 'S' ||
				map[y_cur][x_cur] == 'E' || map[y_cur][x_cur] == 'W')
			{
				count++;
				*player = (t_player){x_cur, y_cur, map[y_cur][x_cur]};
			}
			x_cur++;
		}
		y_cur++;
	}
	return (count);
}

t_map2D	*dup_map2d(t_map2D *map2d)
{
	t_map2D	*dup;
	size_t	cur;

	dup = malloc(sizeof(t_map2D));
	dup->width = map2d->width;
	dup->height = map2d->height;
	dup->map = malloc(sizeof(char *) * (dup->height + 1));
	cur = 0;
	while (cur < dup->height)
	{
		dup->map[cur] = ft_strdup(map2d->map[cur]);
		cur++;
	}
	dup->map[cur] = NULL;
	return (dup);
}
