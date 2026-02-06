/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:32:50 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/06 11:43:39 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_dot(t_dot *dot, int i, int j, char *element)
{
	char	*comma;

	dot->abscissa = j;
	dot->ordinate = i;
	dot->altitude = ft_atoi(element);
	comma = ft_strchr(element, ',');
	if (comma)
		dot->color = ft_atoi_hex(comma + 1);
	else
	{
		if (dot->altitude < 0)
			dot->color = 0x0000FF;
		else if (dot->altitude == 0)
			dot->color = 0x228B22;
		else if (dot->altitude > 0 && dot->altitude < 20)
			dot->color = 0xBB4513;
		else if (dot->altitude > 20)
			dot->color = 0xFFFFFF;
	}
}

static int	get_width_line(char *line)
{
	char	**splits_line;
	int		j;
	int		i;
	char	**alt;

	j = 0;
	splits_line = ft_split(line, ' ');
	if (!splits_line)
		return (-1);
	while (splits_line[j++])
	{
		i = 0;
		alt = ft_split(splits_line[j - 1], ',');
		if (alt[0][i] == '-' || alt[0][i] == '+')
			i++;
		while (alt[0][i++])
			if ((alt[0][i - 1] != '\n' && !ft_isdigit(alt[0][i - 1])) ||
					(alt[0][i - 1] == '\n' && alt[0][i]))
				return (-1);
		if (ft_atol(alt[0]) > INT_MAX
				|| ft_atol(alt[0]) < INT_MIN)
			return (-1);
	}
	return (ft_free((void **)splits_line, j), j - 1);
}

int	get_map_dimensions(char *file, int *height, int *width)
{
	char	*line;
	int		fd;
	int		j;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	*height = 0;
	line = get_next_line(fd);
	*width = get_width_line(line);
	if (*width == 0)
		return (close(fd), 0);
	while(line)
	{
		*height += 1;
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			return (close(fd), 1);
		j = get_width_line(line);
		if (j != *width)
			return (close(fd), 0);
	}
	return (0);
}

static void	set_limits(t_limits *lim, double proj_x, double proj_y)
{
	if (proj_x < lim->min_x)
		lim->min_x = proj_x;
	if (proj_x > lim->max_x)
		lim->max_x = proj_x;
	if (proj_y < lim->min_y)
		lim->min_y = proj_y;
	if (proj_y > lim->max_y)
		lim->max_y = proj_y;
}

t_limits get_map_limits(t_map *map)
{
	t_limits		lim;
	int				i;
	int				j;
	double			proj_x;
	double			proj_y;

	i = -1;
	lim.min_x = INT_MAX;
	lim.max_x = INT_MIN;
	lim.min_y = INT_MAX;
	lim.max_y = INT_MIN;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			iso_project(map->dots[i][j], &proj_x, &proj_y);
			set_limits(&lim, (int)proj_x, (int)proj_y);
		}
	}
	return (lim);
}
