#include <stdio.h>
#include <fcntl.h>
#include "../libft/include/get_next_line.h"

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

	(*result)->map = NULL;
}

char	*ft_strappend(char **dest, char const *str)
{
	char *old_dest;

	old_dest = *dest;
	*dest = ft_strjoin(*dest, str);
	free(old_dest);
	return (*dest);
}

int	is_line_only(char *line, char c)
{
	size_t	cur;
	int		only_c;

	cur = 0;
	while (line[cur] && line[cur + 1] != '\n')
	{
		if (line[cur] != c)
			return (0);
		cur++;
	}
	return (1);
}

int	pass_spaces(char *line, size_t cur)
{
	while (line[cur] == ' ')
		cur++;
	return (cur);
}

int	line_value_size(char *line, size_t cur)
{
	size_t	size;

	size = 0;
	while (line[cur + size] != '\n')
	{
		size++;
		if (is_line_only(line + cur + size, ' ') && line[cur + size + 1] != '\n')
			return (size);
	}
	return (size);
}

char	*get_line_value(int prefix_len, char *line)
{
	size_t	cur;

	cur = pass_spaces(line, prefix_len);
	return (ft_substr(line, cur, line_value_size(line, cur)));
}

char	*print_error(char *error)
{
	printf("%s", error);
	return (NULL);
}

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

char	*decimal_to_hexadecimal(int decimal)
{
	char	*hexadecimal;
	int		cur;

	if (decimal < 0 || decimal > 255)
		return (NULL);
	hexadecimal = ft_calloc(3, sizeof(char));
	ft_memset(hexadecimal, '0', 2);
	cur = 1;
	while (decimal > 0)
	{
		hexadecimal[cur--] =  "0123456789ABCDEF"[decimal % 16];
		decimal /= 16;
	}
	return (hexadecimal);
}

int	str_array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

int	check_rgb_string_format(char *rgb_string)
{
	int	cur;
	int	comma_count;

	cur = 0;
	comma_count = 0;
	while (rgb_string[cur])
	{
		if (rgb_string[cur] == ',')
		{
			comma_count++;
			if (comma_count > 2)
				return (0);
		}
		else if (rgb_string[cur] == '+')
		{
			if (!ft_isdigit(rgb_string[cur + 1]))
				return (0);
		}
		else if (!ft_isdigit(rgb_string[cur]))
			return (0);
		cur++;
	}
	//ft_printf("string: %s, comma_count = %d\n", rgb_string, comma_count);
	return (1);
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
				free(rgb_color);
				free(rgb[0]);
				free(rgb[1]);
				free(rgb[2]);
				free(rgb);
				return (print_error("Error\n(Color value must be between 0 and 255)\n"));
			}
			char	*color_hex = decimal_to_hexadecimal(ft_atoi(rgb[rgb_cur]));
			*color = ft_strappend(color, color_hex);
			free(color_hex);
			rgb_cur++;
		}
		free(rgb_color);
		free(rgb[0]);
		free(rgb[1]);
		free(rgb[2]);
		free(rgb);
	}
		
	return (*color);
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

int	is_line_empty(char *line)
{
	size_t	cur;
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (1);
	return (0);
}

int	str_contains(char *str, char c)
{
	size_t	cur;

	cur = 0;
	while (str[cur])
	{
		if (str[cur] == c)
			return (1);
		cur++;
	}
	return (0);
}

int	check_map_line_char(char *line)
{
	size_t	cur;

	cur = 0;
	while (line[cur] && line[cur] != '\n')
	{
		if (!str_contains(" 10NSEW", line[cur]))
			return (0);
		cur++;
	}
	return (1);
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
	if (map->map)
	{
		cur = 0;
		while (map->map[cur])
		{
			if (map->map[cur])
				free(map->map[cur]);
			cur++;
		}
		free(map->map);
	}
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

size_t	ft_strlcpy2(char *dst, const char *src, size_t size)
{
	size_t	cur;

	if (size == 0)
		return (ft_strlen(src));
	cur = 0;
	while (src[cur] && cur < (size - 1))
	{
		dst[cur] = src[cur];
		cur++;
	}
	//dst[cur] = 0;
	return (ft_strlen(src));
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

t_player	get_player(char **map)
{
	size_t	x_cur;
	size_t	y_cur;

	y_cur = 0;
	while (map[y_cur])
	{
		x_cur = 0;
		while (map[y_cur][x_cur])
		{
			if (map[y_cur][x_cur] == 'N' || map[y_cur][x_cur] == 'S' ||
				map[y_cur][x_cur] == 'E' || map[y_cur][x_cur] == 'W')
				return ((t_player){x_cur, y_cur, map[y_cur][x_cur]});
			x_cur++;
		}
		y_cur++;
	}
	return ((t_player){-1, -1});
}

int	count_players(char **map)
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
				count++;
			x_cur++;
		}
		y_cur++;
	}
	return (count);
}

int	can_exit_map_from_pos(t_parsed *map, size_t x, size_t y)
{
	if (map->map[y][x] == '.' || map->map[y][x] == '1')
		return (0);
	else if (map->map[y][x] == '0')
		map->map[y][x] = '.';
	else if (map->map[y][x] == ' ')
		return (1);

	int	correct_sides;

	correct_sides = 4;
	// left
	correct_sides -= can_exit_map_from_pos(map, x - 1, y);
	// right
	correct_sides -= can_exit_map_from_pos(map, x + 1, y);
	// up
	correct_sides -= can_exit_map_from_pos(map, x, y - 1);
	// down
	correct_sides -= can_exit_map_from_pos(map, x, y + 1);
	return (correct_sides != 4);
}

int	check_map(t_parsed *map)
{
	t_player	player;

	if (count_players(map->map) != 1)
	{
		ft_printf("Error\n(Map contains multiple positions for the player)\n");
		return (0);
	}
	
	player = get_player(map->map);
	if (can_exit_map_from_pos(map, player.x, player.y))
	{
		ft_printf("Error\n(Map is not closed)\n");
		return (0);
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
			else if (!is_line_empty(line))
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
			else if (is_line_empty(line))
				return (free_parsing_elems(result, &map_line, &line, map_fd, "Error\n(The map content contains empty lines)\n"));
			else if (is_line_only(line, ' '))
				return (free_parsing_elems(result, &map_line, &line, map_fd, "Error\n(The map content contains lines with only spaces)\n"));
			else
				map_line = ft_strappend(&map_line, line);
		}

		free(line);
		line = get_next_line(map_fd, GNL_KEEP);
	}

	if (!has_every_data(result))
		return (free_parsed(result));

	result->map = parse_map_line(map_line);
	result->map_height = get_map_height(result->map);
	result->map_width = get_map_width(result->map);
	free(map_line);

	if (!check_map(result))
		return (free_parsed(result));

	// ft_printf("North: |%s|\n", result->north_texture);
	// ft_printf("South: |%s|\n", result->south_texture);
	// ft_printf("East: |%s|\n", result->east_texture);
	// ft_printf("West: |%s|\n", result->west_texture);
	// ft_printf("Floor: |%s|\n", result->floor_color);
	// ft_printf("Ceil: |%s|\n", result->ceil_color);

	int	x = 0;
	while (result->map[x])
	{
		ft_printf("|%s|\n", result->map[x]);
		x++;
	}

	return (result);
}
