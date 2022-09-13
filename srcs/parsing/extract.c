/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:19:04 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/13 16:58:28 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*extract_texture(char *line, t_parsed *map)
{
	char	**texture;
	int		fd;

	texture = NULL;
	if (!ft_strncmp("NO", line, 2))
		texture = &(map->north_texture);
	if (!ft_strncmp("SO", line, 2))
		texture = &(map->south_texture);
	if (!ft_strncmp("EA", line, 2))
		texture = &(map->east_texture);
	if (!ft_strncmp("WE", line, 2))
		texture = &(map->west_texture);

	if (texture)
	{
		if (*texture != NULL)
			return (print_error("Error\n(You can't set a texture more than once)\n"));
		*texture = get_line_value(2, line);

		fd = open(*texture, O_RDONLY);
		if (fd < 0)
			return (print_error("Error\n(Unable to open texture file)\n"));
	}
	return (*texture);
}

int	pos_in_str(char *str, char c)
{
	int	cur;

	cur = 0;
	while (str[cur] != 0)
	{
		if (str[cur] == c)
			return (cur);
		cur++;
	}
	return (-1);
}

void	*extract_color(char *line, t_parsed *map)
{
	char	*color;
	int		*color_num;
	int		cur;

	color_num = NULL;
	if (!ft_strncmp("C", line, 1))
		color_num = &(map->ceil_color);
	else if (!ft_strncmp("F", line, 1))
		color_num = &(map->floor_color);
	else
		return (NULL);

	if (*color_num != -1)
		return (print_error("Error\n(You can't set a color more than once)\n"));
	color = rgb_to_hex(get_line_value(2, line));
	if (!color)
		return (NULL);

	cur = 0;
	*color_num = 0;
	while (color[cur])
	{
		*color_num = *color_num * 16 + pos_in_str("0123456789ABCDEF", color[cur]);
		cur++;
	}
	free(color);
	return ((void *)1);
}
