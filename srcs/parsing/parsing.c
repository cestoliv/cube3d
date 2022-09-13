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

	(*result)->map2D = malloc(sizeof(t_map2D));
	(*result)->map2D->map = NULL;
	(*result)->map2D->width = 0;
	(*result)->map2D->height = 0;

	(*result)->map1D = malloc(sizeof(t_map1D));
	(*result)->map1D->map = NULL;
	(*result)->map1D->width = 0;
	(*result)->map1D->height = 0;
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

void	print_map(t_parsed *map)
{
	int	x;
	int	y;
	int	cur;

	ft_printf("North: |%s|\n", map->north_texture);
	ft_printf("South: |%s|\n", map->south_texture);
	ft_printf("East: |%s|\n", map->east_texture);
	ft_printf("West: |%s|\n", map->west_texture);
	ft_printf("Floor: |#%x|\n", map->floor_color);
	ft_printf("Ceil: |#%x|\n", map->ceil_color);

	ft_printf("\nPlayer\n");
	ft_printf("x: %d, y: %d, dir: %c\n", map->player.x, map->player.y, map->player.dir);

	ft_printf("\n2D map\n");
	x = 0;
	while (map->map2D->map[x])
	{
		ft_printf("|%s|\n", map->map2D->map[x]);
		x++;
	}

	ft_printf("\n1D map\n");
	y = 0;
	cur = 0;
	while (y < map->map1D->height)
	{
		ft_printf("|");
		x = 0;
		while (x < map->map1D->width)
		{
			ft_printf("%d", map->map1D->map[cur]);
			x++;
			cur++;
		}
		ft_printf("|\n");
		y++;
	}
}

void	create_map1D(t_parsed *map)
{
	int	x;
	int	y;
	int	cur;

	map->map1D->width = map->map2D->width;
	map->map1D->height = map->map2D->height;
	map->map1D->map = malloc(sizeof(int) * (map->map1D->width * map->map1D->height));

	y = 0;
	cur = 0;
	while (map->map2D->map[y])
	{
		x = 0;
		while (map->map2D->map[y][x])
		{
			if (ft_str_contains("0NSEW", map->map2D->map[y][x]))
				map->map1D->map[cur] = 0;
			else
				map->map1D->map[cur] = 1;
			cur++;
			x++;
		}
		y++;
	}
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
	{
		ft_printf("Error\n(The map does not contain all the textures and colors information)\n");
		free(map_line);
		return (free_parsed(result));
	}

	if (ft_strlen(map_line) == 0)
	{
		ft_printf("Error\n(The content of the map is empty)\n");
		free(map_line);
		return (free_parsed(result));
	}
	result->map2D->map = parse_map_line(map_line);
	result->map2D->height = get_map_height(result->map2D->map);
	result->map2D->width = get_map_width(result->map2D->map);
	free(map_line);

	if (!check_map(result))
		return (free_parsed(result));

	create_map1D(result);
	get_player(result->map2D->map, &(result->player));

	return (result);
}
