/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:10:19 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/15 18:40:21 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/ft_printf.h"

typedef struct s_player
{
	int		x;
	int		y;
	char	dir;
}	t_player;

typedef struct s_map2D
{
	char	**map;
	size_t	width;
	size_t	height;
}	t_map2D;

typedef struct s_map1D
{
	int		*map;
	size_t	width;
	size_t	height;
}	t_map1D;

typedef struct s_parsed
{
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;

	int			floor_color;
	int			ceil_color;

	t_player	player;
	t_map2D		*map2d;
	t_map1D		*map1d;
}	t_parsed;

t_parsed	*parse(char *file_path);

// FREE
void		*free_parsed(t_parsed *map);
int			free_map2d(t_map2D *map2D);
void		*free_parsing_el(t_parsed *map, char **str1, char **str2, int fd);
void		free_rgb(char *rgb_line, char **rgb);

// FT_UTILS
size_t		ft_strlcpy2(char *dst, const char *src, size_t size);
char		*ft_strappend(char **dest, char const *str);
int			ft_is_only(char *line, char c);
int			ft_is_empty(char *line);
int			ft_str_contains(char *str, char c);

// RGB
char		*decimal_to_hexadecimal(int decimal);
int			check_rgb_string_format(char *rgb_string);
char		*rgb_to_hex(char *rgb);

// EXTRACT
char		*extract_texture(char *line, t_parsed *map);
void		*extract_color(char *line, t_parsed *map);
char		*get_line_value(int prefix_len, char *line);

// ERROR
char		*print_error(char *error);

// MAP 2D
t_map2D		*dup_map2d(t_map2D *map2D);
int			get_player(char **map, t_player *player);
size_t		get_map_width(char **map);
size_t		get_map_height(char **map);

// PARSE MAP
char		**parse_map_line(char *map_line);

// PARSE FILE
char		*parse_map_file(char *file_path, t_parsed *parsed);
int			check_map_line_char(char *line);
int			has_every_data(t_parsed *map);

// CHECK MAP
int			check_map(t_parsed *map);
int			count_correct_sides(t_map2D *map2D, size_t x, size_t y);
int			can_exit_map_from_pos(t_map2D *map2D, size_t x, size_t y);

#endif
