#include <stdio.h>
#include <fcntl.h>
#include "../libft/include/get_next_line.h"

typedef struct s_parsed
{
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;

	char	*floor_color;
	char	*ceil_color;
}	t_parsed;

void	init_parsed_struct(t_parsed *result)
{
	result->north_texture = NULL;
	result->south_texture = NULL;
	result->east_texture = NULL;
	result->west_texture = NULL;

	result->floor_color = NULL;
	result->ceil_color = NULL;
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
	// Pour s'arrêter au prenier espace dans la valeur
	// while (line[cur + size] != ' ' && line[cur + size] != '\n')
	// 	size++;
	while (line[cur + size] != '\n')
		size++;
	return (size);
}

char	*get_line_value(char *prefix, char *line)
{
	size_t	cur;

	cur = pass_spaces(line, ft_strlen(prefix));
	return (ft_substr(line, cur, line_value_size(line, cur)));
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
	// free(map->north_texture);
	// free(map->south_texture);
	// free(map->east_texture);
	// free(map->west_texture);
	// free(map->floor_color);
	// free(map->ceil_color);
	return (NULL);
}

t_parsed	*parse(char *file_path)
{
	t_parsed	*result;

	init_parsed_struct(result);
	int	map_fd = open(file_path, O_RDONLY);

	char *map_line = ft_strdup("");
	int has_map_started = 0;
	char *line = get_next_line(map_fd, GNL_KEEP);
	while (line != NULL)
	{
		if (!has_map_started)
		{
			if (!ft_strncmp("NO", line, 2))
				result->north_texture = get_line_value("NO", line);
			else if (!ft_strncmp("SO", line, 2))
				result->south_texture = get_line_value("SO", line);
			else if (!ft_strncmp("EA", line, 2))
				result->east_texture = get_line_value("EA", line);
			else if (!ft_strncmp("WE", line, 2))
				result->west_texture = get_line_value("WE", line);
			else if (!ft_strncmp("F", line, 1))
				result->floor_color = get_line_value("F", line);
			else if (!ft_strncmp("C", line, 1))
				result->ceil_color = get_line_value("C", line);
			else if (!is_line_empty(line))
				has_map_started = 1;
		}
		if (has_map_started)
		{
			if (!has_every_data(result))
				return (free_parsed(result));
			if (!check_map_line_char(line))
				return (free_parsed(result));
			else if (is_line_empty(line))
				return (free_parsed(result));
			else
			{
				map_line = ft_strjoin(map_line, line);
			}
		}

		line = get_next_line(map_fd, GNL_KEEP);
	}

	printf("Map line:\n%s\n", map_line);
	return (result);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	t_parsed *map = parse("maps/m1.cub");
	// if (map == NULL)
	// {
	// 	printf("KO\n");
	// 	return (1);
	// }
	printf("North: |%s|\n", map->north_texture);
	printf("South: |%s|\n", map->south_texture);
	printf("East: |%s|\n", map->east_texture);
	printf("West: |%s|\n", map->west_texture);
	printf("Floor: |%s|\n", map->floor_color);
	printf("Ceil: |%s|\n", map->ceil_color);
}
