/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 23:50:47 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/06 09:56:23 by vnaoussi         ###   ########.fr       */
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
		*((unsigned int*)(img->data + index)) = color;
	}
}

void	draw_lign(t_img *img, t_proj_dot dot_a, t_proj_dot dot_b)
{
	int		err[2];
	int		step[2];
	double	percent;
	int		delta[2];
	int		i;

	step[0] = get_step((int)dot_a.proj_x, (int)dot_b.proj_x);
	step[1] = get_step((int)dot_a.proj_y, (int)dot_b.proj_y);
	delta[0] = abs((int)dot_b.proj_x - (int)dot_a.proj_x);
	delta[1] = abs((int)dot_b.proj_y - (int)dot_a.proj_y);
	err[0] = delta[0] - delta[1];
	i = 0;
	while (1)
	{
		percent = (double)i++ / fmax(delta[0], delta[1]);
		put_pixel(img, (int)dot_a.proj_x, (int)dot_a.proj_y,
				get_color((int)dot_a.color, (int)dot_b.color, percent));
		if ((int)dot_a.proj_x == (int)dot_b.proj_x
				&& (int)dot_a.proj_y == (int)dot_b.proj_y)
			return ;
		err[1] = 2 * err[0];
		if (err[1] > -delta[1])
		{
			err[0] -= delta[1];
			dot_a.proj_x += step[0];
		}
		if (err[1] < delta[0])
		{
			err[0] += delta[0];
			dot_a.proj_y += step[1];
		}
	}
}
