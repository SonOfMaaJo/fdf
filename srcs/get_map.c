/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/11 15:00:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_width_line(char *line)
{
	char	**s;
	int		j;
	int		i;
	char	**alt;

	s = ft_split(line, ' ');
	if (!s)
		return (-1);
	j = 0;
	while (s[j])
	{
		alt = ft_split(s[j], ',');
		i = (alt[0][0] == '-' || alt[0][0] == '+');
		while (alt[0][i])
			if (!ft_isdigit(alt[0][i++]))
				return (ft_free_s(alt), ft_free_s(s), -1);
		if (ft_atol(alt[0]) > 2147483647 || ft_atol(alt[0]) < -2147483648)
			return (ft_free_s(alt), ft_free_s(s), -1);
		ft_free_s(alt);
		j++;
	}
	return (ft_free_s(s), j);
}

int	get_map_dimensions(char *file, int *height, int *width)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 0);
	find_n(line);
	*width = get_width_line(line);
	*height = 0;
	while (line)
	{
		(*height)++;
		if (get_width_line(line) != *width)
			return (free(line), close(fd), 0);
		free(line);
		line = get_next_line(fd);
		if (line)
			find_n(line);
	}
	return (close(fd), 1);
}
