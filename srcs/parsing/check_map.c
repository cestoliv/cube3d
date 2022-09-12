/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:32:07 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/12 10:34:52 by ocartier         ###   ########.fr       */
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

int	can_exit_map_from_pos(t_map2D *map2D, size_t x, size_t y)
{
	int	correct_sides;
	
	if (map2D->map[y][x] == '.' || map2D->map[y][x] == '1')
		return (0);
	else if (map2D->map[y][x] == '0')
		map2D->map[y][x] = '.';
	else if (map2D->map[y][x] == ' ')
		return (1);

	correct_sides = 4;
	// left
	if (x - 1 >= map2D->width)
		correct_sides--;
	else
		correct_sides -= can_exit_map_from_pos(map2D, x - 1, y);
	// right
	if (x + 1 >= map2D->width)
		correct_sides--;
	else
		correct_sides -= can_exit_map_from_pos(map2D, x + 1, y);
	// up
	if (y - 1 >= map2D->height)
		correct_sides--;
	else
		correct_sides -= can_exit_map_from_pos(map2D, x, y - 1);
	// down
	if (y + 1 >= map2D->height)
		correct_sides--;
	else
		correct_sides -= can_exit_map_from_pos(map2D, x, y + 1);
	return (correct_sides != 4);
}

int	check_map(t_parsed *map)
{
	t_player	player;
	t_map2D		*map2D_dup;

	if (get_player(map->map2D->map, &player) != 1)
	{
		ft_printf("Error\n(Map contains multiple positions for the player)\n");
		return (0);
	}
	
	map2D_dup = dup_map2D(map->map2D);
	if (can_exit_map_from_pos(map2D_dup, player.x, player.y))
	{
		ft_printf("Error\n(Map is not closed)\n");
		free_map2D(map2D_dup);
		return (0);
	}
	free_map2D(map2D_dup);
	return (1);
}
