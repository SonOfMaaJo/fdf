/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:28:04 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/05 19:05:49 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(int start, int end, double percentage)
{
	int	r;
	int	g;
	int	b;

	r = get_light((start >> 16) & 0xFF, (end >> 16) & 0xFF, percentage);
	g = get_light((start >> 8) & 0xFF, (end >> 8) & 0xFF, percentage);
	b = get_light(start & 0xFF, end & 0xFF, percentage);
	return ((r << 16) | (g << 8) | b);
}

static void	get_z_min_max(t_map *map, double *min, double *max)
{
	int	i;
	int	j;

	*min = map->dots[0][0].altitude;
	*max = map->dots[0][0].altitude;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->dots[i][j].altitude < *min)
				*min = map->dots[i][j].altitude;
			if (map->dots[i][j].altitude > *max)
				*max = map->dots[i][j].altitude;
		}
	}
}

static void	set_default_color(t_dot *dot, double min_z, double max_z)
{
	double	p;

	if (max_z == min_z)
		p = 0;
	else
		p = (dot->altitude - min_z) / (max_z - min_z);
	if (p < 0.5)
		dot->color = get_color(0x1E90FF, 0x228B22, p * 2);
	else
		dot->color = get_color(0x228B22, 0xFFFFFF, (p - 0.5) * 2);
}

void	color_map(t_map *map)
{
	int		i;
	int		j;
	double	min_z;
	double	max_z;

	get_z_min_max(map, &min_z, &max_z);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->dots[i][j].color == -1)
				set_default_color(&(map->dots[i][j]), min_z, max_z);
		}
	}
}
