/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 23:50:47 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/08 01:01:24 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		index = (y * img->size_line) + (x * (img->bit_per_pixel / 8));
		*((unsigned int *)(img->data + index)) = color;
	}
}

static void	calculate_step_delta(t_proj_dot a, t_proj_dot b, int step[2],
	int delta[2])
{
	step[0] = get_step(a.proj_x, b.proj_x);
	step[1] = get_step(a.proj_y, b.proj_y);
	delta[0] = abs(b.proj_x - a.proj_x);
	delta[1] = abs(b.proj_y - a.proj_y);
}

static void	update_pos(t_proj_dot *a, int step[2], int delta[2], int err[2])
{
	err[1] = 2 * err[0];
	if (err[1] > -delta[1])
	{
		err[0] -= delta[1];
		a->proj_x += step[0];
	}
	if (err[1] < delta[0])
	{
		err[0] += delta[0];
		a->proj_y += step[1];
	}
}

void	draw_lign(t_img *img, t_proj_dot dot_a, t_proj_dot dot_b)
{
	int		err[2];
	int		step[2];
	int		delta[2];
	int		i;

	calculate_step_delta(dot_a, dot_b, step, delta);
	err[0] = delta[0] - delta[1];
	i = 0;
	while (1)
	{
		put_pixel(img, dot_a.proj_x, dot_a.proj_y,
			get_color(dot_a.color, dot_b.color,
				(double)i++ / fmax(delta[0], delta[1])));
		if (dot_a.proj_x == dot_b.proj_x && dot_a.proj_y == dot_b.proj_y)
			break ;
		update_pos(&dot_a, step, delta, err);
	}
}
