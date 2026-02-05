/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 23:50:47 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/05 19:08:23 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_index(t_img *img, int x, int y)
{
	return ((y * img->size_line) + (x * (img->bit_per_pixel / 8)));
}

static int	get_step(int n, int m)
{
	if (n < m)
		return (1);
	else
		return (-1);
}

static void	put_pixel(t_img *img, int x, int y, int color)
{
	int	index;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		index = get_index(img, x, y);
		(img->data)[index] = color;
	}
}

static int	bresenham_trick(int *err, int n, int m, int sign)
{
	int	er;

	er = 2 * (*err);
	if (sign)
	{
		if (er > -1 * abs(m - n))
		{
			*err -= abs(m - n);
			return (1);
		}
	}
	else
	{
		if (er < abs(m - n))
		{
			*err += abs(m - n);
			return (1);
		}
	}
	return (0);
}

void	draw_lign(t_img *img, t_proj_dot dot_a, t_proj_dot dot_b)
{
	int		err;
	int		s[2];
	int		xy[2];
	double	percent;
	int		i;

	s[0] = get_step(dot_a.proj_x, dot_b.proj_x);
	s[1] = get_step(dot_a.proj_y, dot_b.proj_y);
	err = abs(dot_b.proj_x - dot_a.proj_x) - abs(dot_b.proj_y - dot_a.proj_y);
	xy[0] = dot_a.proj_x;
	xy[1] = dot_a.proj_y;
	i = 0;
	while (1)
	{
		percent = i / (fmax(dot_b.proj_x - dot_a.proj_x,
					dot_b.proj_y - dot_a.proj_x));
		put_pixel(img, xy[0], xy[1], get_color(dot_a.color,
				dot_b.color, percent));
		if (xy[0] == dot_b.proj_x && xy[1] == dot_b.proj_y)
			return ;
		if (bresenham_trick(&err, dot_a.proj_x, dot_b.proj_x, 1))
			xy[0] += s[0];
		if (bresenham_trick(&err, dot_a.proj_y, dot_b.proj_y, 0))
			xy[1] += s[1];
	}
}
