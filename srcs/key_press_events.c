/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:07:18 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/06 18:22:51 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zoom_in_out(void *param, int keysym)
{
	t_fdf_win_g	*fdf_g;

	fdf_g = (t_fdf_win_g *)param;
	if (keysym == KEY_ZOOM_P)
		(fdf_g->map)->zoom += 1;
	if (keysym == KEY_ZOOM_M)
		(fdf_g->map)->zoom -= 1;
	set_offset(fdf_g->map, fdf_g->map->limits);
}

static void	reset_print_amod(void *param)
{
	t_fdf_win_g *fdf_g;

	fdf_g = (t_fdf_win_g *)param;
	clear_image(fdf_g->img);
	fill_img_with_pixel_dots(&(fdf_g->img), fdf_g->map, (fdf_g->map)->height,
			(fdf_g->map)->width);
	mlx_put_image_to_window(fdf_g->mlx, fdf_g->win, fdf_g->img->img_ptr, 0, 0);
}

int	handle_keypress(int keysym, void *param)
{
	if (keysym == KEY_ESC)
		exit_program(param);
	else if (keysym == KEY_ZOOM_P || keysym == KEY_ZOOM_M)
		zoom_in_out(param, keysym);
	reset_print_amod(param);
	return (0);
}

