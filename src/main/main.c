
#include "../../include/cub3d.h"

void	game_usage(void)
{
	printf("%s\n", USAGE);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc == 2)
	{
		init_cub(&cub);
		parse_file(&cub, argv[1]);
	}
	game_usage();
	return (SUCCESS);
}

