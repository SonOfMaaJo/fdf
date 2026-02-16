/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:42:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/16 17:23:55 by vnaoussi         ###   ########.fr       */
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

	if (!table)
		return ;
	i = 0;
	while (table[i])
		free(table[i++]);
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

int	inits_map(char *file, int	*width, int *height, t_map **map)
{
	t_limits	lim;

	*map = (t_map *)malloc(sizeof(t_map));
	if (!(*map))
		return (perror("allocation fail"), 0);
	(*map)->dots = get_dot_from(file, height, width);
	if (!((*map)->dots))
	{
		free(*map);
		*map = NULL;
		return (0);
	}
	(*map)->width = *width;
	(*map)->height = *height;
	color_map(*map);
	set_initial_factor(*map);
	if (!init_proj_dots(*map))
		return (0);
	lim = get_map_limits(*map);
	set_zoom(*map, lim);
	set_offset(*map, lim);
	(*map)->limits = lim;
	return (1);
}
