/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 23:04:25 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/06 10:11:24 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_proj_dot	**get_dots_2d(t_map map, int height, int width)
{
	t_proj_dot	**dots_2d;
	double		proj_x;
	double		proj_y;
	int			i;
	int			j;

	dots_2d = (t_proj_dot **)malloc(sizeof(t_proj_dot *) * height);
	if (!dots_2d)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		dots_2d[i] = (t_proj_dot *)malloc(sizeof(t_proj_dot) * width);
		if (!dots_2d[i])
			return (ft_free((void **)dots_2d, i), NULL);
		j = -1;
		while (++j < width)
		{
			iso_project(map.dots[i][j], &proj_x, &proj_y);
			dots_2d[i][j].proj_x = proj_x * map.zoom + map.offset_x;
			dots_2d[i][j].proj_y = proj_y * map.zoom + map.offset_y;
			dots_2d[i][j].color = (map.dots[i][j]).color;
		}
	}
	return (dots_2d);
}

void	fill_img_with_pixel_dots(t_img **img, t_map *map, int height, int width)
{
	int			i;
	int			j;

	map->proj_dots = get_dots_2d(*map, height, width);
	if (!map->proj_dots)
		return ;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (j < width - 1)
				draw_lign(*img, (map->proj_dots)[i][j],
						(map->proj_dots)[i][j+1]);
			if (i < height - 1)
				draw_lign(*img, (map->proj_dots)[i][j],
						(map->proj_dots)[i + 1][j]);
		}
	}
}
