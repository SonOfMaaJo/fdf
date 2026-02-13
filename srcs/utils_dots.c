/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 23:04:25 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/08 00:59:09 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_dot(t_dot *dot, int i, int j, char *element)
{
	char	*comma;

	dot->abscissa = (double)j;
	dot->ordinate = (double)i;
	dot->altitude = (double)ft_atoi(element);
	comma = ft_strchr(element, ',');
	if (comma)
		dot->color = ft_atoi_hex(comma + 1);
	else
		dot->color = -1;
}

static void	compute_projections(t_map *map, int height, int width)
{
	int			i;
	int			j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			transform_and_project(map->dots[i][j], map,
				&(map->proj_dots[i][j].proj_x),
				&(map->proj_dots[i][j].proj_y));
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
