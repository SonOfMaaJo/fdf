/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 23:04:25 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/06 20:00:09 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	compute_projections(t_map *map, int height, int width)
{
	double		proj_x;
	double		proj_y;
	int			i;
	int			j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			iso_project(map->dots[i][j], &proj_x, &proj_y, map->z_divisor);
			map->proj_dots[i][j].proj_x = (int)((proj_x * map->zoom) + map->offset_x);
			map->proj_dots[i][j].proj_y = (int)((proj_y * map->zoom) + map->offset_y);
			map->proj_dots[i][j].color = (map->dots[i][j]).color;
		}
	}
}

void	fill_img_with_pixel_dots(t_img **img, t_map *map, int height, int width)
{
	int			i;
	int			j;

	compute_projections(map, height, width);
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (j < width - 1)
				draw_lign(*img, (map->proj_dots)[i][j],
						(map->proj_dots)[i][j + 1]);
			if (i < height - 1)
				draw_lign(*img, (map->proj_dots)[i][j],
						(map->proj_dots)[i + 1][j]);
		}
	}
}
