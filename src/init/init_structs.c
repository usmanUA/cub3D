/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:01:10 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/30 14:01:12 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_vecs(t_cub *cub, int exit_fail)
{
	// TODO: ALSO free what these vecs hold

	vec_free(cub->textures_fds);
	free(cub->textures_fds);
	vec_free(cub->direction_info);
	free(cub->direction_info);
	vec_free(cub->floor);
	free(cub->floor);
	vec_free(cub->ceiling);
	free(cub->ceiling);
	vec_free(cub->map);
	free(cub->map);
	if (exit_fail == YES)
		exit(EXIT_FAILURE);
}

void	check_free_exit(t_cub *cub)
{
	if (cub->textures_fds == NULL)
		exit(EXIT_FAILURE);
	if (cub->direction_info == NULL)
		exit(EXIT_FAILURE);
	if (cub->ceiling == NULL)
		exit(EXIT_FAILURE);
	if (cub->floor == NULL)
		exit(EXIT_FAILURE);
	if (cub->map == NULL)
		exit(EXIT_FAILURE);
}


void	init_inds(t_indices *inds)
{
	inds->st = 0;
	inds->end = 0;
	inds->counter = 3;
}

void	init_tex_count(t_count *count)
{
	count->no = 0;
	count->so = 0;
	count->ea = 0;
	count->we = 0;
	count->f = 0;
	count->c = 0;
}

static	void	init_vecs(t_cub *cub)
{
	vec_new(cub->textures_fds, 0, sizeof(int));
	vec_new(cub->direction_info, 0, sizeof(int));
	vec_new(cub->ceiling, 0, sizeof(int));
	vec_new(cub->floor, 0, sizeof(int));
	vec_new(cub->map, 0, sizeof(char **));
}

static	void	alloc_init_vecs(t_cub *cub)
{
	t_vec	*textures_fds;
	t_vec	*direction_info;
	t_vec	*ceiling;
	t_vec	*floor;
	t_vec	*map;

	textures_fds = (t_vec *)malloc(sizeof(t_vec));
	cub->textures_fds = textures_fds;
	check_free_exit(cub);
	direction_info	= (t_vec *)malloc(sizeof(t_vec));
	cub->direction_info = direction_info;
	check_free_exit(cub);
	ceiling	= (t_vec *)malloc(sizeof(t_vec));
	cub->ceiling = ceiling;
	check_free_exit(cub);
	floor	= (t_vec *)malloc(sizeof(t_vec));
	cub->floor = floor;
	check_free_exit(cub);
	map = (t_vec *)malloc(sizeof(t_vec));
	cub->map = map;
	check_free_exit(cub);
	init_vecs(cub);
}

void	init_cub(t_cub *cub)
{
	cub->dir_info = 0;
	cub->line = NULL;
	alloc_init_vecs(cub);
}
