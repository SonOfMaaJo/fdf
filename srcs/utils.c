/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:32:50 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/09 00:29:17 by vnaoussi         ###   ########.fr       */
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

static int	get_width_line(char *line)
{
	char	**splits_line;
	int		j;
	int		i;
	char	**alt;

	alt = NULL;
	find_n(line);
	j = 0;
	splits_line = ft_split(line, ' ');
	if (!splits_line)
		return (-1);
	while (splits_line[j++])
	{
		i = 0;
		if (alt)
			ft_free_s(alt);
		alt = ft_split(splits_line[j - 1], ',');
		if (alt[0][i] == '-' || alt[0][i] == '+')
			i++;
		while (alt[0][i++])
			if (!ft_isdigit(alt[0][i - 1]))
				return (ft_free_s(alt), ft_free_s(splits_line), -1);
		if (ft_atol(alt[0]) > INT_MAX
				|| ft_atol(alt[0]) < INT_MIN)
			return (ft_free_s(alt), ft_free_s(splits_line), -1);
	}
	return (ft_free_s(alt), ft_free_s(splits_line), j - 1);
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
	if (!line)
		return (close(fd), 0);
	*width = get_width_line(line);
	if (*width <= 0)
		return (free(line), close(fd), 0);
	while (line)
	{
		*height += 1;
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			j = get_width_line(line);
			if (j != *width)
				return (free(line), close(fd), 0);
		}
	}
	return (close(fd), 1);
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
			if (map->projection_type)
			{
				proj_x = map->dots[i][j].abscissa;
				proj_y = map->dots[i][j].ordinate;
			}
			else
				iso_project(map->dots[i][j], &proj_x, &proj_y, map->z_divisor);
			set_limits(&lim, (int)proj_x, (int)proj_y);
		}
	}
	return (lim);
}
