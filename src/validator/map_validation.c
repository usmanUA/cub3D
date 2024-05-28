
#include "../../include/cub3d.h"

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
		exit(EXIT_FAILURE); // NOTE: free mem
	}
}

int	dir_char(char c)
{
	if (c == 'W' || c == 'N')
		return (1);
	if (c == 'S' || c == 'E')
		return (1);
	return (0);
}

void	check_wall_unit(t_cub *cub, char **line, char c)
{
	if (c != '1')
	{
		free(*line);
		exit(EXIT_FAILURE); // TODO: free mem, print error
	}
}

void	check_dir_info(t_cub *cub, char **line, char c)
{
	if (cub->dir_info > 0)
	{
		free(*line);
		exit(EXIT_FAILURE); // TODO: free mem, print error
	}
}

void	validate_middle(t_cub *cub, char **line)
{
	int	ind;
	char	c;

	// NOTE: check if the middle line is all 1?
	ind = 0;
	c = (*line)[ind];
	check_wall_unit(cub, line, c);
	while ((*line)[++ind] != '\n') // TODO: change logic if end is \n
	{
		c = (*line)[ind];
		if (dir_char(c))
		{
			check_dir_info(cub, line, c);
			cub->dir_info++;
			continue;
		}
		if (c != '1' && c != '0')
		{
			free(*line);
			exit(EXIT_FAILURE); // TODO: free mem, print error
		}
		if ((*line)[ind+1] == '\n') // TODO: adjust to \n if last char is \n
			break;
	}
	check_wall_unit(cub, line, c);
}

void	validate_horizontal(t_cub *cub, char **line)
{
	int	ind;

	ind = -1;
	while ((*line)[++ind]) // TODO: change logic if end is \n
	{
		if ((*line)[++ind] != '1')
		{
			free(*line);
			exit(EXIT_FAILURE); // TODO: free mem, print error
		}
	}
}

int	open_validate_file(t_cub *cub, char *map_path, char *ext)
{
	size_t	path_len;
	size_t	bfr_ext;
	int	fd;

	fd = -2;
	fd = open(map_path, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		// TODO: free cub
		file_error(map_path, YES);
	}
	path_len = ft_strlen(map_path);
	bfr_ext = path_len - 4;
	if (ft_strncmp(ext, &map_path[path_len], path_len - bfr_ext))
		// TODO: free cub
		file_error(map_path, 42);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		// TODO: free cub
		file_error(map_path, YES);
	return (fd);
}
