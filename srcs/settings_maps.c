/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_maps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:05:35 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/08 02:44:36 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_proj_dots(t_map *map)
{
	int	i;

	map->proj_dots = (t_proj_dot **)malloc(sizeof(t_proj_dot *)
			* map->height);
	if (!map->proj_dots)
		return (ft_free((void **)map->dots, map->height), free(map), 0);
	i = -1;
	while (++i < map->height)
	{
		map->proj_dots[i] = (t_proj_dot *)malloc(sizeof(t_proj_dot)
				* map->width);
		if (!map->proj_dots[i])
			return (ft_free((void **)map->dots, map->height),
				ft_free((void **)(map->proj_dots), i), free(map), 0);
	}
	return (1);
}

void	set_zoom(t_map *map, t_limits lim)
{
	map->zoom = fmin(WIN_WIDTH / (lim.max_x - lim.min_x), WIN_HEIGHT
			/ (lim.max_y - lim.min_y));
	if (map->zoom < 1)
		map->zoom = 1;
}

void	set_initial_factor(t_map *map)
{
	map->z_divisor = 4.0;
	map->projection_type = 0;
	map->shear_factor = 0;
	map->angle_x = 0;
	map->angle_y = 0;
	map->angle_z = 0;
	map->trans.trans_x = 0;
	map->trans.trans_y = 0;
}

void	set_offset(t_map *map, t_limits lim)
{
	map->offset_x = (WIN_WIDTH / 2) - ((lim.max_x + lim.min_x) / 2)
		* map->zoom;
	map->offset_y = (WIN_HEIGHT / 2) - ((lim.max_y + lim.min_y) / 2)
		* map->zoom;
}
