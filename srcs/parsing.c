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

	(*result)->floor_color = NULL;
	(*result)->ceil_color = NULL;

	(*result)->map2D = malloc(sizeof(t_map2D));
	(*result)->map2D->map = NULL;
	(*result)->map2D->width = 0;
	(*result)->map2D->height = 0;
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
	if (map->floor_color)
		count++;
	if (map->ceil_color)
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

t_parsed	*parse(char *file_path)
{
	t_parsed	*result;

	init_parsed_struct(&result);
	int	map_fd = open(file_path, O_RDONLY);
	if (map_fd < 0)
	{
		ft_printf("Error\n(Unable to open the map file)\n");
		return (free_parsed(result));
	}

	char *map_line = ft_strdup("");
	int has_map_started = 0;
	char *line = get_next_line(map_fd, GNL_KEEP);
	while (line != NULL)
	{
		if (!has_map_started)
		{
			if (!ft_strncmp("NO", line, 2) || !ft_strncmp("SO", line, 2) ||
				!ft_strncmp("EA", line, 2) || !ft_strncmp("WE", line, 2))
			{
				if (!extract_texture(line, result))
					return (free_parsing_elems(result, &map_line, &line, map_fd, ""));
			}
			else if (!ft_strncmp("F", line, 1) || !ft_strncmp("C", line, 1))
			{
				if (!extract_color(line, result))
					return (free_parsing_elems(result, &map_line, &line, map_fd, ""));
			}
			else if (!ft_is_empty(line))
			{
				has_map_started = 1;
			}
		}
		if (has_map_started)
		{
			if (!has_every_data(result))
				return (free_parsing_elems(result, &map_line, &line, map_fd, "Error\n(The map does not contain all the textures and colors information)\n"));
			if (!check_map_line_char(line))
				return (free_parsing_elems(result, &map_line, &line, map_fd, "Error\n(The map content contains invalid characters)\n"));
			else if (ft_is_empty(line))
				return (free_parsing_elems(result, &map_line, &line, map_fd, "Error\n(The map content contains empty lines)\n"));
			else if (ft_is_only(line, ' '))
				return (free_parsing_elems(result, &map_line, &line, map_fd, "Error\n(The map content contains lines with only spaces)\n"));
			else
				map_line = ft_strappend(&map_line, line);
		}

		free(line);
		line = get_next_line(map_fd, GNL_KEEP);
	}

	if (!has_every_data(result))
		return (free_parsed(result));

	result->map2D->map = parse_map_line(map_line);
	result->map2D->height = get_map_height(result->map2D->map);
	result->map2D->width = get_map_width(result->map2D->map);
	free(map_line);

	if (!check_map(result))
		return (free_parsed(result));

	// ft_printf("North: |%s|\n", result->north_texture);
	// ft_printf("South: |%s|\n", result->south_texture);
	// ft_printf("East: |%s|\n", result->east_texture);
	// ft_printf("West: |%s|\n", result->west_texture);
	// ft_printf("Floor: |%s|\n", result->floor_color);
	// ft_printf("Ceil: |%s|\n", result->ceil_color);

	// int	x = 0;
	// while (result->map2D->map[x])
	// {
	// 	ft_printf("|%s|\n", result->map2D->map[x]);
	// 	x++;
	// }

	return (result);
}
