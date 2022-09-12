#include "../include/parsing.h"

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	t_parsed *map = parse(argv[1]);
	if (!map)
		return (1);
	ft_printf("MAP OK.\n");
	// print_map(map);
	free_parsed(map);
}
