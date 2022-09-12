/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:10:19 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/12 15:02:52 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

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

	char		*floor_color;
	char		*ceil_color;

	t_player	player;
	t_map2D		*map2D;
	t_map1D		*map1D;
}	t_parsed;

t_parsed	*parse(char *file_path);
void		print_map(t_parsed *map);

// FREE
void		*free_parsed(t_parsed *map);
int			free_map2D(t_map2D *map2D);
void		*free_parsing_elems(t_parsed *map, char **str1, char **str2, int fd, char *error);
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

// EXTRACT
char		*extract_texture(char *line, t_parsed *map);
char		*extract_color(char *line, t_parsed *map);
char		*get_line_value(int prefix_len, char *line);

// ERROR
char		*print_error(char *error);

// MAP 2D
t_map2D		*dup_map2D(t_map2D *map2D);

// PARSE MAP
char		**parse_map_line(char *map_line);

// CHECK MAP
int			check_map(t_parsed *map);
int			get_player(char **map, t_player *player);
size_t		get_map_height(char **map);
size_t		get_map_width(char **map);

#endif
