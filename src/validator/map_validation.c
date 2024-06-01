/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:01:33 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/30 14:01:35 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stdio.h>

void	skip_spaces(char *s, int *ind);

void	file_error(char *path, int use_errno)
{
	if (use_errno == YES)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_putstr_fd("", 2);
	}
	ft_putendl_fd("Give a Valid map path", 1);
	exit(EXIT_FAILURE);
}

void	validate_type_identifier(t_cub *cub, char **type_id)
{
	if (ft_strlen(*type_id) > 1)
	{
		free(*type_id);
		free_vecs(cub, NULL, YES, YES);
	}
}

int	direction_char(char c)
{
	if (c == 'W' || c == 'N')
		return (YES);
	if (c == 'S' || c == 'E')
		return (YES);
	return (NA);
}

char	check_wall_unit(t_cub *cub, int *ind, int first)
{
	char	c;

	if (first == YES)
		skip_spaces(*cub->line, ind);
	c = (*cub->line)[*ind];
	if (c != '1')
		free_vecs(cub, NULL, YES, YES);
	return (c);
}

void	check_direction_info(t_cub *cub, char c)
{
	if (cub->dir_info > 0)
		free_vecs(cub, NULL, YES, YES);
	cub->dir_info++;
}

void	check_zero_presence(t_cub *cub)
{
	int	ind;

	ind = -1;
	while (*cub->line[++ind])
	{
		if (*cub->line[ind] == '0')
			return;
	}
	free_vecs(cub, NULL, YES, YES);
}

char	ones_surround_spaces(t_cub *cub, char c, char prev_c, int *ind)
{
	if (ft_isspace(c) && prev_c != '1')
		free_vecs(cub, NULL, YES, YES);
	if (ft_isspace(c) && prev_c == '1')
	{
		skip_spaces(*cub->line, ind);
		c = (*cub->line)[*ind];
		if (c != '1')
			free_vecs(cub, NULL, YES, YES);
	}
	return (c);
}

void	validate_middle(t_cub *cub)
{
	int	ind;
	char	c;
	char	prev_c;

	check_zero_presence(cub);
	ind = 0;
	prev_c = check_wall_unit(cub, &ind, YES);
	c = *cub->line[++ind];
	// FIX: 10000N1
	while ((*cub->line)[ind+1])
	{
		c = ones_surround_spaces(cub, c, prev_c, &ind);
		if (direction_char(c) == YES)
			check_direction_info(cub, c);
		else if (c != '1' && c != '0')
			free_vecs(cub, NULL, YES, YES);
		prev_c = c;
		c = (*cub->line)[++ind];
	}
	check_wall_unit(cub, &ind, NA);
}

void	validate_horizontal(t_cub *cub)
{
	int	ind;
	int	len;

	ind = 0;
	len = ft_strlen(*cub->line);
	skip_spaces(*cub->line, &ind);
	if (*cub->line[ind] != '1')
		free_vecs(cub, NULL, YES, YES);
	ind = -1;
	while (++ind < (len - 1))
	{
		if ((*cub->line)[ind] != '1' && !ft_isspace(*cub->line[ind]))
			free_vecs(cub, NULL, YES, YES);
	}
	if (*cub->line[ind] != '1')
		free_vecs(cub, NULL, YES, YES);
}

int	open_validate_file(t_cub *cub, char *map_path, char *ext, int texture_path)
{
	size_t	path_len;
	size_t	bfr_ext;
	int	fd;

	fd = -2;
	path_len = ft_strlen(map_path);
	printf("path_len: %zu\n", path_len);
	bfr_ext = path_len - 4;
	printf("bfr_ext: %zu\n", bfr_ext);
//	printf("ext: %s and ext from path: %s\n", ext, &map_path)
	if (ft_strncmp(ext, &map_path[bfr_ext], path_len - bfr_ext))
		free_vecs(cub, NULL, YES, YES);
	printf("here\n");
	fd = open(map_path, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		free_vecs(cub, NULL, YES, NO);
		file_error(map_path, YES);
	}
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		free_vecs(cub, NULL, YES, NO);
		file_error(map_path, YES);
	}
	if (texture_path == YES)
	{
		close(fd);
		fd = 1;
	}
	return (fd);
}
