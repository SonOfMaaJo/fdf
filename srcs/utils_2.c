/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:42:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/05 19:01:12 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free(void **table, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(table[i++]);
	free(table);
}

int	set_map(char *file, int	*width, int *height, t_map **map)
{
	t_limits	lim;
	float		zoom;

	*map = (t_map *)malloc(sizeof(t_map));
	if (!(*map))
		return (0);
	(*map)->dots = get_dot_from(file, height, width);
	if (!((*map)->dots))
		return (free(*map), 0);
	lim = get_map_limits(*map);
	zoom = fmin(WIN_WIDTH / (lim.max_x - lim.min_x), WIN_HEIGHT
			/ (lim.max_y - lim.min_y)) * 0.8;
	if (zoom < 1)
		zoom = 1;
	(*map)->offset_x = (WIN_WIDTH / 2) - ((lim.max_x + lim.min_x) / 2) * zoom;
	(*map)->offset_y = (WIN_HEIGHT / 2) - ((lim.max_y + lim.min_y) / 2)
		* zoom;
	(*map)->limits = lim;
	(*map)->zoom = zoom;
	(*map)->width = lim.max_x - lim.min_x;
	(*map)->height = lim.max_y - lim.min_y;
	return (1);
}
