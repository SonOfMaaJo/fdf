/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:32:50 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/11 15:15:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_limits(t_limits *lim, double proj_x, double proj_y)
{
	if (proj_x < lim->min_x)
		lim->min_x = proj_x;
	if (proj_x > lim->max_x)
		lim->max_x = proj_x;
	if (proj_y < lim->min_y)
		lim->min_y = proj_y;
	if (proj_y > lim->max_y)
		lim->max_y = proj_y;
}

static void	get_proj(t_map *map, t_dot dot, double *px, double *py)
{
	if (map->projection_type)
	{
		*px = dot.abscissa;
		*py = dot.ordinate;
	}
	else
		iso_project(dot, px, py, map->z_divisor);
}

t_limits	get_map_limits(t_map *map)
{
	t_limits		lim;
	int				i;
	int				j;
	double			px;
	double			py;

	i = -1;
	lim.min_x = 2147483647;
	lim.max_x = -2147483648;
	lim.min_y = 2147483647;
	lim.max_y = -2147483648;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			get_proj(map, map->dots[i][j], &px, &py);
			set_limits(&lim, px, py);
		}
	}
	return (lim);
}
