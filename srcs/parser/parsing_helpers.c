/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:12:22 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/07 15:12:23 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

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

