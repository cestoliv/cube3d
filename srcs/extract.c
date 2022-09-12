/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:19:04 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/12 10:19:40 by ocartier         ###   ########.fr       */
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

char	*extract_color(char *line, t_parsed *map)
{
	char	**color;
	int		fd;

	color = NULL;
	if (!ft_strncmp("C", line, 1))
		color = &(map->ceil_color);
	if (!ft_strncmp("F", line, 1))
		color = &(map->floor_color);

	if (color)
	{
		if (*color != NULL)
			return (print_error("Error\n(You can't set a color more than once)\n"));
		*color = ft_strdup("#");
		char *rgb_color = get_line_value(2, line);
		if (!check_rgb_string_format(rgb_color))
		{
			free(rgb_color);
			return (print_error("Error\n(Invalid RGB color format)\n"));
		}
		char **rgb = ft_split(rgb_color, ',');
		int rgb_cur = 0;
		while (rgb[rgb_cur])
		{
			if (ft_atoi(rgb[rgb_cur]) > 255 || ft_atoi(rgb[rgb_cur]) < 0)
			{
				free_rgb(rgb_color, rgb);
				return (print_error("Error\n(Color value must be between 0 and 255)\n"));
			}
			char	*color_hex = decimal_to_hexadecimal(ft_atoi(rgb[rgb_cur]));
			*color = ft_strappend(color, color_hex);
			free(color_hex);
			rgb_cur++;
		}
		free_rgb(rgb_color, rgb);
	}
		
	return (*color);
}
