/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_transformations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:33:31 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/07 20:26:25 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_map **map)
{
	double	previous_y;
	double	previous_z;
	t_map	*map_sec;
	int		i;
	int		j;

	map_sec = *map;
	i = -1;
	while (++i < map_sec->height)
	{
		j = -1;
		while (++j < map_sec->width)
		{
			previous_y = ((map_sec->dots)[i][j]).ordinate;
			previous_z = ((map_sec->dots)[i][j]).altitude;
			((map_sec->dots)[i][j]).abscissa = previous_y
				* cos(map_sec->angle_x) + previous_z * sin(map_sec->angle_x);
			((map_sec->dots)[i][j]).ordinate = -1 * previous_y
				* sin(map_sec->angle_x) + previous_z * cos(map_sec->angle_x);
		}
	}
}

void	rotate_y(t_map **map)
{
	double	previous_x;
	double	previous_z;
	t_map	*map_sec;
	int		i;
	int		j;

	map_sec = *map;
	i = -1;
	while (++i < map_sec->height)
	{
		j = -1;
		while (++j < map_sec->width)
		{
			previous_x = ((map_sec->dots)[i][j]).abscissa;
			previous_z = ((map_sec->dots)[i][j]).altitude;
			((map_sec->dots)[i][j]).abscissa = previous_x
				* cos(map_sec->angle_y) + previous_z * sin(map_sec->angle_y);
			((map_sec->dots)[i][j]).ordinate = -1 * previous_x
				* sin(map_sec->angle_y) + previous_z * cos(map_sec->angle_y);
		}
	}
}

void	rotate_z(t_map **map)
{
	double	previous_x;
	double	previous_y;
	t_map	*map_sec;
	int		i;
	int		j;

	map_sec = *map;
	i = -1;
	while (++i < map_sec->height)
	{
		j = -1;
		while (++j < map_sec->width)
		{
			previous_x = ((map_sec->dots)[i][j]).abscissa;
			previous_y = ((map_sec->dots)[i][j]).ordinate;
			((map_sec->dots)[i][j]).abscissa = previous_x
				* cos(map_sec->angle_z) - previous_y * sin(map_sec->angle_z);
			((map_sec->dots)[i][j]).ordinate = previous_x
				* sin(map_sec->angle_z) + previous_y * cos(map_sec->angle_z);
		}
	}
}

void	iso_project(t_dot dot, double *proj_x, double *proj_y, double z_divisor)
{
	*proj_x = (dot.abscissa - dot.ordinate) * cos(0.523599);
	*proj_y = -1 * (dot.altitude / z_divisor) + (dot.abscissa
			+ dot.ordinate) * sin(0.523599);
}
