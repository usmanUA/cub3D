
#ifndef MACROS_H
# define MACROS_H

#define	USAGE "USAGE:\n\t./cub3D <mapfile>\n"

enum	e_type_identifiers
{
	TEXTURE,
	CEILING,
	FLOOR,
};

enum	e_flags
{
	SUCCESS,
	FAILURE,
	YES,
	NA,
	EMP_LINE,
	TOT_TIDS = 6,
};

enum	e_directions
{
	SO,
	NO,
	WE,
	EA,
};


#endif
