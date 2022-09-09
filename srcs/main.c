#include "../include/parsing.h"

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	t_parsed *map = parse(argv[1]);
	if (!map)
		return (1);
	ft_printf("MAP OK.\n");
	free_parsed(map);

	// int	map_fd = open(argv[1], O_RDONLY);
	// char *line = get_next_line(map_fd, GNL_KEEP);
	// ft_printf("line: %s", line);
	// free(line);
	// line = get_next_line(map_fd, GNL_CLEAR);
	// ft_printf("line: %s", line);
	// free(line);
}
