
#include "../../include/cub3d.h"

void	init_tex_count(t_count *count);

void	eof_malloc_check(t_cub *cub, char *line, int malloc_flag)
{
	// TODO: take this function where gnl is called
	if (line == NULL && malloc_flag == 1)
		exit(EXIT_FAILURE); // TODO: free mem
	if (line == NULL && malloc_flag == 0)
		exit(EXIT_FAILURE); // TODO: free mem, print error
}

void	free_exit(t_cub *cub, char **type_id)
{
	free(type_id);
	exit(EXIT_FAILURE); // TODO: free mem (cub)
}

int	space_until_end(char *line)
{
	int	ind;

	ind = -1;
	while (line[++ind])
	{
		if (!ft_isspace(line[ind]))
			return (NO);
	}
	return (YES);
}

void	skip_spaces(char *s, int *ind)
{
	while (s[*ind] != '\0' && ft_isspace(s[*ind]))
		++(*ind);
}

int	all_digits(char *rgb)
{
	int	ind;

	ind = -1;
	while (rgb[++ind])
	{
		if (!ft_isdigit(rgb[ind]))
			return (42);
	}
	return (YES);
}

void	check_invalid_color(t_cub *cub, t_indices *inds, char **rgb)
{
	skip_spaces(*cub->line, &inds->end);
	if (!ft_isspace(*cub->line[inds->end]))
	{
		free(*rgb);
		exit(EXIT_FAILURE); // TODO: free mem, print error
	}
}

char	*next_rgb(t_cub *cub, t_indices *inds)
{
	char	*rgb;
	char	*line;
	int	end;

	line = *cub->line;
	inds->st = inds->end;
	skip_spaces(*cub->line, &inds->st);
	end = inds->st;
	if (line[end] == '\0')
		exit(EXIT_FAILURE); // TODO: free mem, print error
	while (line[end] && !ft_isspace(line[end]) && line[end] != ',')
		++end;
	inds->end = end;
	rgb = ft_substr(*cub->line, inds->st, inds->end);
	if (rgb == NULL)
		exit(EXIT_FAILURE); // TODO: free mem, print error
	if (all_digits(rgb) != YES)
	{
		free(rgb);
		exit(EXIT_FAILURE); // TODO: free mem, print error
	}
	--inds->counter;
	if (inds->counter == 0)
		check_invalid_color(cub, inds, &rgb);
	return (rgb);
}

void	skip_comma(t_cub *cub, t_indices *inds)
{
	skip_spaces(*cub->line, &inds->end);
	if (*cub->line[inds->end] != ',')
		exit(EXIT_FAILURE); // TODO: free mem, print error
	inds->end++;
}

void	parse_color(t_cub *cub, t_indices *inds, int type)
{
	char	*rgb_s;
	int	rgb_n;
	int	count;

	count = -1;
	while (inds->counter && ++count < 3)
	{
		rgb_s = next_rgb(cub, inds);
		rgb_n = ft_atoi(rgb_s);
		free(rgb_s);
		if (type == FLOOR)
		{
			if (vec_push(cub->floor, &rgb_n) == 0)
				free_exit(cub, &rgb_s);
		}
		else if (type == CEILING)
		{
			if (vec_push(cub->ceiling, &rgb_n) == 0)
				free_exit(cub, &rgb_s);
		}
		skip_comma(cub, inds);
	}
	if (inds->counter)
		exit(EXIT_FAILURE); // TODO: free mem, print error
}

void	parse_push_colors(t_cub *cub, char **type_id, t_indices *inds)
{
	if (!ft_strncmp(*type_id, "C", 1))
	{
		free(*type_id);
		parse_color(cub, inds, CEILING);
		return ;
	}
	if (!ft_strncmp(*type_id, "F", 1))
	{
		free(*type_id);
		parse_color(cub, inds, FLOOR);
		return;
	}
	free_exit(cub, type_id);
}

void	ea_identifier(t_cub *cub, char **type_id, int *type_info, t_count *count)
{
	count->ea++;
	if (count->ea > 2)
		free_exit(cub, type_id);
	*type_info = EA;
}

void	identifiers_type(t_cub *cub, char **type_id, int *type_info, t_count *count)
{	
	if (!ft_strncmp(*type_id, "NO", 2))
	{
		count->no++;
		if (count->no > 2)
			free_exit(cub, type_id);
		*type_info = NO;
	}
	if (!ft_strncmp(*type_id, "SO", 2))
	{
		count->so++;
		if (count->so > 2)
			free_exit(cub, type_id);
		*type_info = SO;
	}
	if (!ft_strncmp(*type_id, "WE", 2))
	{
		count->we++;
		if (count->we > 2)
			free_exit(cub, type_id);
		*type_info = WE;
	}
	if (!ft_strncmp(*type_id, "EA", 2))
		ea_identifier(cub, type_id, type_info, count);
}

int	type_identifier(t_cub *cub, t_indices *inds, t_count *count)
{
	char	*type_id;
	int	type_id_info;

	type_id_info = 42;
	type_id = ft_substr(*cub->line, inds->st, inds->end);
	if (type_id == NULL)
		exit(EXIT_FAILURE); // TODO: free mem
	identifiers_type(cub, &type_id, &type_id_info, count);
	if (type_id_info != 42)
	{
		if (vec_push(cub->direction_info, &type_id_info) == 0)
			free_exit(cub, &type_id);
		return (TEXTURE);
	}
	validate_type_identifier(cub, &type_id);
	parse_push_colors(cub, &type_id, inds);
	return (42);
}

void	parse_push_textures(t_cub *cub, t_indices *inds)
{
	char	*path;
	int	fd;
	int	ind;

	inds->st = inds->end;
	skip_spaces(*cub->line, &inds->st);
	if (*cub->line[inds->st] == '\0')
		exit(EXIT_FAILURE); // TODO: free mem, print error
	inds->end = inds->st;
	while ((*cub->line)[inds->end] && !ft_isspace((*cub->line)[inds->end]))
		++inds->end;
	ind = inds->end;
	skip_spaces(*cub->line, &ind);
	if (*cub->line[ind] != '\0')
		exit(EXIT_FAILURE); // TODO: free mem, print error
	path = ft_substr(*cub->line, inds->st, inds->end);
	if (path == NULL) // NOTE: malloc_fail
		exit(EXIT_FAILURE); // TODO: free mem
	fd = open_validate_file(cub, path, ".xpm");
	free(path);
	if (vec_push(cub->textures_fds, &fd) == 0)
	{
		close(fd);
		exit(EXIT_FAILURE); // TODO: free mem
	}
}

int	parse_push_lineinfo(t_cub *cub, int fd, t_count *count)
{
	t_indices	inds;
	char		type_id;
	char		c;
	int		malloc_flag;

	inds.st = 0;
	inds.end = 0;
	inds.counter = 3;
	malloc_flag = 0;
	*cub->line = get_next_line(fd, malloc_flag);
	eof_malloc_check(cub, *cub->line, malloc_flag);
	if (*cub->line == NULL) // NOTE: malloc_fail or empty file?
		exit(EXIT_FAILURE); // TODO: free mem
	skip_spaces(*cub->line, &inds.st);
	c = *cub->line[inds.st];
	if (c == '1' || c == '\n')
	{
		free(*cub->line);
		if (c == '\0')
			return (42);
		return (0);
	}
	inds.end = inds.st;
	while ((*cub->line)[inds.end] && !ft_isspace((*cub->line)[inds.end]))
		++inds.end;
	if (type_identifier(cub, &inds, count) == TEXTURE)
		parse_push_textures(cub, &inds);
	return (42);
}

void	parse_until_map(t_cub *cub, int fd)
{
	char	*line;
	int	qontinue;
	t_count	count;

	init_tex_count(&count);
	qontinue = 42;
	while (qontinue)
		qontinue = parse_push_lineinfo(cub, fd, &count);
}

void	validate_push_horizontal(t_cub *cub, char **line)
{
	char	*dup_line;

	validate_horizontal(cub, line);
	dup_line = ft_strdup(*line);
	free(*line);
	if (vec_push(cub->map, &dup_line) == 0)
	{
		free(dup_line);
		exit(EXIT_FAILURE); // TODO: free mem
	}
}

void	validate_push_middle(t_cub *cub, char **line)
{
	char	*dup_line;

	validate_middle(cub, line);
	dup_line = ft_strdup(*line);
	free(*line);
	if (vec_push(cub->map, &dup_line) == 0)
	{
		free(dup_line);
		exit(EXIT_FAILURE); // TODO: free mem
	}
}

void	parse_map(t_cub *cub, int fd)
{
	char	*line;
	int	malloc_flag;

	malloc_flag = 0;
	line = get_next_line(fd, malloc_flag);
	eof_malloc_check(cub, line, malloc_flag);
	validate_push_horizontal(cub, &line);
	while (line)
	{
		line = get_next_line(fd, malloc_flag);
		eof_malloc_check(cub, line, malloc_flag);
		validate_push_middle(cub, &line);
	}
}

void	parse_file(t_cub *cub, char *map_path)
{
	int	fd;

	fd = open_validate_file(cub, map_path, ".cub");
	parse_until_map(cub, fd);
	parse_map(cub, fd);
}
