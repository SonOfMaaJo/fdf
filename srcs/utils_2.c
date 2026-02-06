/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:42:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/06 16:28:10 by vnaoussi         ###   ########.fr       */
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

void	ft_free_s(char **table)
{
	int	i;

	i = 0;
	while(table[i++])
		free(table[i - 1]);
	free(table);
}

void	find_n(char *line)
{
	char	*p;

	p = ft_strchr(line, '\n');
	if (p)
		*p = '\0';
}

void	clear_image(t_img *img)
{
	int	total_bytes;

	total_bytes = WIN_HEIGHT * img->size_line;
	ft_bzero(img->data, total_bytes);
}

int	set_map(char *file, int	*width, int *height, t_map **map)
{
	t_limits	lim;
	float		zoom;

	if (!map);
		*map = (t_map *)malloc(sizeof(t_map));
	if (!(*map))
		return (0);
	(*map)->dots = get_dot_from(file, height, width);
	if (!((*map)->dots))
		return (free(*map), 0);
	(*map)->width = *width;
	(*map)->height = *height;
	(*map)->z_divisor = 4.0;
	(*map)->projection_type = 0;
	(*map)->shear_factor = 0;
	(*map)->proj_dots = (t_proj_dot **)malloc(sizeof(t_proj_dot *) * (*height));
	if (!(*map)->proj_dots)
		return (ft_free((void **)(*map)->dots, *height), free(*map), 0);
	int i = -1;
	while (++i < *height)
	{
		(*map)->proj_dots[i] = (t_proj_dot *)malloc(sizeof(t_proj_dot) * (*width));
		if (!(*map)->proj_dots[i])
			return (ft_free((void **)(*map)->dots, *height),
					ft_free((void **)(*map)->proj_dots, i), free(*map), 0);
	}
	lim = get_map_limits(*map);
	zoom = fmin(WIN_WIDTH / (lim.max_x - lim.min_x), WIN_HEIGHT
			/ (lim.max_y - lim.min_y));
	if (zoom < 1)
		zoom = 1;
	(*map)->offset_x = (WIN_WIDTH / 2) - ((lim.max_x + lim.min_x) / 2) * zoom;
	(*map)->offset_y = (WIN_HEIGHT / 2) - ((lim.max_y + lim.min_y) / 2)
		* zoom;
	(*map)->limits = lim;
	(*map)->zoom = zoom;
	return (1);
}
