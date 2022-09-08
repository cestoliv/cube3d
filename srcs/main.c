#include "../include/parsing.h"

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	t_parsed *map = parse(argv[1]);
	if (!map)
		return (1);
	ft_printf("MAP OK.\n");
}
