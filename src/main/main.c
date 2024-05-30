/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:00:41 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/30 14:00:43 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

