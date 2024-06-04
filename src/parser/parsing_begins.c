/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_begins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:01:20 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/30 14:01:22 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_tex_count(t_count *count);
void	init_inds(t_indices *inds);

void	next_strings_end(char *line, int *end, int check_comma)
{
	char	c;

	c = line[*end];
	while (c && !ft_isspace(c))
	{
		if (check_comma && c == ',')
			break ;
		++(*end);
		c = line[*end];
	}
}

void	eof_malloc_check(t_cub *cub, int malloc_flag, int map, int fd)
{
	// TODO: take this function where gnl is called
	if (*cub->line == NULL && malloc_flag == 1)
	{
		close(fd);
		free_vecs(cub, YES, NO);
	}
	if (*cub->line == NULL && malloc_flag == 0 && map == NA)
	{
		close(fd);
		free_vecs(cub, YES, YES);
	}
}

void	free_exit(t_cub *cub, char **type_id, int print_err)
{
	free(*type_id);
	free_vecs(cub, YES, print_err);
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

void	check_invalid_color(t_cub *cub, char *line, t_indices *inds, char **rgb)
{
	skip_spaces(line, &inds->end);
	if (line[inds->end] != '\0' && !ft_isspace(line[inds->end]))
	{
		free(*rgb);
		free_vecs(cub, YES, YES);
	}
}

char	*next_rgb(t_cub *cub, char *line, t_indices *inds)
{
	char	*rgb;

	inds->st = inds->end;
	skip_spaces(line, &inds->st);
	inds->end = inds->st;
	if (line[inds->st] == '\0')
		free_vecs(cub, YES, YES);
	next_strings_end(line, &inds->end, 1);
	rgb = ft_substr(line, inds->st, inds->end - inds->st);
	if (rgb == NULL)
		free_vecs(cub, YES, NO);
	if (all_digits(rgb) != YES)
	{
		// TODO: look for negative rgb values
		free(rgb);
		free_vecs(cub, YES, YES);
	}
	--inds->counter; // NOTE: might not need this counter
	if (inds->counter == 0) // NOTE: might not need this counter
		check_invalid_color(cub, *cub->line, inds, &rgb);
	return (rgb);
}

void	skip_comma(t_cub *cub, char *line, t_indices *inds, int count)
{
	if (count == 2)
		return ;
	inds->st = inds->end;
	skip_spaces(line, &inds->st);
	if (line[inds->st] != ',')
		free_vecs(cub, YES, YES);
	inds->st++;
	inds->end = inds->st;
}

void	parse_color(t_cub *cub, t_indices *inds, int type)
{
	char	*rgb_s;
	int	rgb_n;
	int	count;

	count = -1;
	while (inds->counter && ++count < 3) // NOTE: might not need this counter
	{
		rgb_s = next_rgb(cub, *cub->line, inds);
		rgb_n = ft_atoi(rgb_s);
		free(rgb_s);
		if (type == FLOOR)
		{
			if (vec_push(cub->floor, &rgb_n) == 0)
				free_exit(cub, &rgb_s, NO);
		}
		else if (type == CEILING)
		{
			if (vec_push(cub->ceiling, &rgb_n) == 0)
				free_exit(cub, &rgb_s, NO);
		}
		skip_comma(cub, *cub->line, inds, count);
	}
	if (inds->counter) // NOTE: might not need this counter
		free_vecs(cub, YES, YES);
}

void	parse_push_colors(t_cub *cub, char **type_id, t_indices *inds, t_count *count)
{
	if (!ft_strncmp(*type_id, "C", 1))
	{
		count->c++;
		if (count->c > 1)
			free_exit(cub, type_id, YES);
		free(*type_id);
		parse_color(cub, inds, CEILING);
		return ;
	}
	if (!ft_strncmp(*type_id, "F", 1))
	{
		count->f++;
		if (count->f > 1)
			free_exit(cub, type_id, YES);
		free(*type_id);
		parse_color(cub, inds, FLOOR);
		return;
	}
	free_exit(cub, type_id, YES); // TODO: print error
}

void	ea_identifier(t_cub *cub, char **type_id, int *type_info, t_count *count)
{
	count->ea++;
	if (count->ea > 1)
		free_exit(cub, type_id, YES);
	*type_info = EA;
}

void	identifiers_type(t_cub *cub, char **type_id, int *type_info, t_count *count)
{	
	if (!ft_strncmp(*type_id, "NO", 2))
	{
		count->no++;
		if (count->no > 1)
			free_exit(cub, type_id, YES);
		*type_info = NO;
	}
	if (!ft_strncmp(*type_id, "SO", 2))
	{
		count->so++;
		if (count->so > 1)
			free_exit(cub, type_id, YES);
		*type_info = SO;
	}
	if (!ft_strncmp(*type_id, "WE", 2))
	{
		count->we++;
		if (count->we > 1)
			free_exit(cub, type_id, YES);
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
	type_id = NULL;
	type_id = ft_substr(*cub->line, inds->st, inds->end - inds->st);
	if (type_id == NULL)
		free_vecs(cub, YES, NO);
	identifiers_type(cub, &type_id, &type_id_info, count);
	if (type_id_info != 42)
	{
		free(type_id);
		if (vec_push(cub->textures_info, &type_id_info) == 0)
			free_exit(cub, &type_id, NO);
		return (TEXTURE);
	}
	validate_type_identifier(cub, &type_id);
	parse_push_colors(cub, &type_id, inds, count);
	return (42);
}

void	parse_push_textures(t_cub *cub, t_indices *inds)
{
	char	*path;
	char	*line;
	int	end;

	line = *cub->line;
	inds->st = inds->end;
	skip_spaces(line, &inds->st);
	if (line[inds->st] == '\0')
		free_vecs(cub, YES, YES);
	inds->end = inds->st;
	next_strings_end(line, &inds->end, 0);
	// NOTE: the next 3 lines check if path is not followed by a spaces/+newline
	end = inds->end;
	skip_spaces(line, &end);
	if (end < (int)ft_strlen(line) && line[end] != '\0')
		free_vecs(cub, YES, YES);
	path = ft_substr(*cub->line, inds->st, inds->end - inds->st);
	if (path == NULL) // NOTE: malloc_fail
		free_vecs(cub, YES, NO);
	open_validate_file(cub, path, ".xpm", YES);
	if (vec_push(cub->textures_paths, &path) == 0)
	{
		free(path);
		free_vecs(cub, YES, NO);
	}
}

int	parse_push_lineinfo(t_cub *cub, int fd, t_count *count)
{
	t_indices	inds;
	char		c;
	int		malloc_flag;
	char		*line;

	init_inds(&inds);
	malloc_flag = 0;
	*cub->line = get_next_line(fd, &malloc_flag);
	line = *cub->line;
	eof_malloc_check(cub, malloc_flag, NA, fd);
	skip_spaces(*cub->line, &inds.st);
	c = line[inds.st];
	if (c == '1' || c == '\0')
	{
		if (c == '\0')
		{
			free(*cub->line);
			*cub->line = NULL;
			return (EMP_LINE);
		}
		return (NA);
	}
	inds.end = inds.st;
	next_strings_end(*cub->line, &inds.end, 0);
	if (type_identifier(cub, &inds, count) == TEXTURE)
		parse_push_textures(cub, &inds);
	free(*cub->line);
	*cub->line = NULL;
	return (YES);
}

void	parse_until_map(t_cub *cub, int fd)
{
	int	qontinue;
	t_count	count;
	int	tids;

	init_tex_count(&count);
	qontinue = 42;
	tids = 0;
	while (qontinue != NA)
	{
		qontinue = parse_push_lineinfo(cub, fd, &count);
		if (qontinue == YES)
			tids++;
	}
	if (tids < TOT_TIDS)
		free_vecs(cub, YES, YES);
}

void	validate_push_horizontal(t_cub *cub, char **line)
{
	char	*dup_line;

	validate_horizontal(cub, *line);
//	printf("fuck here\n");
	dup_line = ft_strdup(*line); // TODO: do something for whitespaces?
	free(*line);
	if (vec_push(cub->map, &dup_line) == 0)
	{
		free(dup_line);
		free_vecs(cub, YES, NO);
	}
}

void	validate_push_middle(t_cub *cub)
{
	char	*dup_line;

	validate_middle(cub, *cub->line);
	dup_line = ft_strdup(*cub->line);
	free(*cub->line);
	if (vec_push(cub->map, &dup_line) == 0)
	{
		free(dup_line);
		free_vecs(cub, YES, NO);
	}
}

int	last_line(t_cub *cub, char *line)
{
	int	ind;
	int	len;
	int	count;

	ind = -1;
	count = 0;
	len = ft_strlen(line);
	while (++ind < len)
	{
		if (!ft_isspace(line[ind]))
			break ;
	}
	if (ind == len)
		free_vecs(cub, YES, YES);
	ind = -1;
	while (++ind < len)
	{
		count++;
		skip_spaces(line, &ind);
		if (count != 1 && line[ind] == '\0')
			break ;
		if (line[ind] != '1')
			return (NA);
	}
	return (YES);
}

void	something_follows_map(t_cub *cub, int fd)
{
	char	*line;
	int	malloc_flag;
	int	ind;

	malloc_flag = 0;
	ind = -1;
	line = get_next_line(fd, &malloc_flag);
	eof_malloc_check(cub, &malloc_flag, NA, fd);
	while (line)
	{
		ind = 0;
		while (line[ind])
		{
			if (!ft_isspace(line[ind]))
				free_exit(cub, &line, YES);
			ind++;
		}
		free(line);
		line = get_next_line(fd, &malloc_flag);
		eof_malloc_check(cub, malloc_flag, NA, fd);
	}
}

void	parse_map(t_cub *cub, int fd)
{
	int	malloc_flag;
	char	*line;

	malloc_flag = 0;
	validate_push_horizontal(cub, cub->line);
	*cub->line = get_next_line(fd, &malloc_flag);
	eof_malloc_check(cub, malloc_flag, YES, fd);
	while (*cub->line)
	{
		line = get_next_line(fd, &malloc_flag);
		if (last_line(cub, *cub->line) == YES && (!line || line[0] == '\0'))
			break ;
		printf("line: %s\n", *cub->line);
		if (*cub->line[0] == '\0' || *cub->line[0] == '0')
			free_vecs(cub, YES, YES);
		validate_push_middle(cub);
		*cub->line = line;
		eof_malloc_check(cub, malloc_flag, YES, fd);
	}
	if (*cub->line == NULL || cub->dir_info == 0)
		free_vecs(cub, YES, YES);
	validate_push_horizontal(cub, &(*cub->line));
	something_follows_map(cub, fd);
}

void	parse_file(t_cub *cub, char *map_path)
{
	char	*line;
	int	fd;

	line = NULL;
	cub->file = map_path;
	cub->line = &line;
	fd = open_validate_file(cub, map_path, ".cub", NA);
	parse_until_map(cub, fd);
	parse_map(cub, fd);
	cub->line = NULL;
	close(fd);
}
