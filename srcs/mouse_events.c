/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:43:42 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/07 18:57:48 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zoom_in_out(void *param, int button)
{
	t_fdf_win_g	*fdf_g;

	fdf_g = (t_fdf_win_g *)param;
	if (button == 4)
		(fdf_g->map)->zoom += 1;
	else if (button == 5)
	{
		if (fdf_g->map->zoom > 1)
			fdf_g->map->zoom -= 1;
	}
	else
		return ;
	set_offset(fdf_g->map, fdf_g->map->limits);
}

void	reset_print_amod(void *param)
{
	t_fdf_win_g	*fdf_g;

	fdf_g = (t_fdf_win_g *)param;
	clear_image(fdf_g->img);
	fill_img_with_pixel_dots(&(fdf_g->img), fdf_g->map, (fdf_g->map)->height,
		fdf_g->map->width);
	mlx_put_image_to_window(fdf_g->mlx, fdf_g->win, fdf_g->img->img_ptr, 0, 0);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	zoom_in_out(param, button);
	reset_print_amod(param);
	return (1);
}
