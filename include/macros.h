/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:39:04 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/31 14:39:06 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

#define	USAGE "USAGE:\n\t./cub3D <mapfile>\n"

enum	e_type_identifiers
{
	TEXTURE,
	CEILING,
	FLOOR,
	MAP,
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
