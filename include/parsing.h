#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/ft_printf.h"

typedef struct s_parsed
{
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;

	char	*floor_color;
	char	*ceil_color;

	char	**map;
}	t_parsed;

typedef struct s_player
{
	int		x;
	int		y;
	char	dir;
}	t_player;

t_parsed	*parse(char *file_path);
void		*free_parsed(t_parsed *map);

#endif
