
#ifndef CUB3D_H
# define CUB3D_H


#include "macros.h"
#include "../vec/include/vec.h"
#include "../get_next_line/get_next_line.h"
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
	t_vec	*textures_fds;
	t_vec	*direction_info;
	t_vec	*floor;	
	t_vec	*ceiling;	
	t_vec	*map;
}	t_cub;


void	init_cub(t_cub *cub);
int	valid_map(char **argv);
void	validate_horizontal(t_cub *cub);
void	validate_middle(t_cub *cub, char **line);
int	open_validate_file(t_cub *cub, char *map_path, char *ext);
void	validate_type_identifier(t_cub *cub, char **type_id);
void	parse_file(t_cub *cub, char *map_path);

#endif
