/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:00:00 by gemini-cli        #+#    #+#             */
/*   Updated: 2026/02/06 00:48:39 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	print_map_debug(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->dots)
	{
		printf("Debug: Map or Dots is NULL\n");
		return ;
	}
	printf("\n--- DEBUG: FULL MAP CONTENT ---\n");
	printf("Dimensions: %d x %d | Zoom: %d\n", map->width, map->height, map->zoom);
	printf("Offsets: x=%.2f, y=%.2f\n", map->offset_x, map->offset_y);
	printf("Limites : min_x=%d, min_y=%d, max_x=%d, max_y=%d", (map->limits).min_x, (map->limits).min_y, (map->limits).max_x, (map->limits).max_y);
	printf("-------------------------------\n");

	i = 0;
	while (i < map->height)
	{
		j = 0;
		printf("Row %d: ", i);
		while (j < map->width)
		{
			printf("[%d,%d,z:%d,c:0x%X] ",
				map->dots[i][j].abscissa,
				map->dots[i][j].ordinate,
				map->dots[i][j].altitude,
				map->dots[i][j].color);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("--- END OF DEBUG ---\n\n");
}
