/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:05:43 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/31 17:05:45 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	file_error(char *path, int use_errno);

static	void	free_lines(t_cub *cub, int lines)
{
	int	ind;

	ind = -1;
	if (lines == TEXTURE)
	{
		while (++ind < cub->textures_paths->len)
			free(*(char **)vec_get(cub->textures_paths, ind));
	}
	else if (lines == MAP)
	{
		while (++ind < cub->map->len)
			free(*(char **)vec_get(cub->map, ind));
	}
}

void	free_vecs(t_cub *cub, char *map_path, int exit_fail, int print_err)
{
	// TODO: ALSO free what these vecs hold

	if (print_err == YES)
	{
		file_error(map_path, 42);
	}
	if (cub->line && *cub->line)
		free(*cub->line);
	if (cub->textures_paths && cub->textures_paths->len)
		free_lines(cub, TEXTURE);
	vec_free(cub->textures_paths);
	free(cub->textures_paths);
	vec_free(cub->textures_info);
	free(cub->textures_info);
	vec_free(cub->floor);
	free(cub->floor);
	vec_free(cub->ceiling);
	free(cub->ceiling);
	if (cub->map && cub->map->len)
		free_lines(cub, MAP);
	vec_free(cub->map);
	free(cub->map);
	if (exit_fail == YES)
		exit(EXIT_FAILURE);
}

void	freecub_exit(t_cub *cub)
{
	free(cub->textures_paths);
	free(cub->textures_info);
	free(cub->map);
	free(cub->ceiling);
	free(cub->floor);
	exit(EXIT_FAILURE);
}


