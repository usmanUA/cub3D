/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:38:53 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/31 14:38:55 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include "macros.h"
#include "get_next_line.h"
#include "../vec/include/vec.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

typedef	struct	s_indices
{
	int	st;
	int	end;
	int	counter;
}	t_indices;

typedef	struct	s_count
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_count;

typedef struct	s_cub
{
	int	dir_info;
	char	**line;
	char	*file;
	t_vec	*textures_paths;
	t_vec	*textures_info;
	t_vec	*floor;	
	t_vec	*ceiling;	
	t_vec	*map;
}	t_cub;


void	init_cub(t_cub *cub);
int	valid_map(char **argv);
void	validate_horizontal(t_cub *cub, char *line);
void	validate_middle(t_cub *cub, char *line);
int	open_validate_file(t_cub *cub, char *map_path, char *ext, int texture_path);
void	validate_type_identifier(t_cub *cub, char **type_id);
void	parse_file(t_cub *cub, char *map_path);

void	free_vecs(t_cub *cub, int exit_fail, int print_err);
#endif
