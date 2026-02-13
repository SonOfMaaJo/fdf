/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:07:18 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/10 16:03:28 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	reset_map(void	*param)
{
	t_fdf_win_g	*fdf_g;
	t_limits	lim;

	fdf_g = (t_fdf_win_g *)param;
	set_initial_factor(fdf_g->map);
	lim = get_map_limits(fdf_g->map);
	set_zoom(fdf_g->map, lim);
	set_offset(fdf_g->map, lim);
	fdf_g->map->limits = lim;
	reset_print_amod(param);
}

static void	translate_map(int keysym, void	*param)
{
	t_fdf_win_g	*fdf_g;

	fdf_g = (t_fdf_win_g *)param;
	if (keysym == KEY_DIR_UP)
		fdf_g->map->trans.trans_y -= 10;
	else if (keysym == KEY_DIR_DOWN)
		fdf_g->map->trans.trans_y += 10;
	else if (keysym == KEY_DIR_RIGHT)
		fdf_g->map->trans.trans_x += 10;
	else if (keysym == KEY_DIR_LEFT)
		fdf_g->map->trans.trans_x -= 10;
	reset_print_amod(param);
}

static	void	relief_change(int keysym, void *param)
{
	t_fdf_win_g	*fdf_g;

	fdf_g = (t_fdf_win_g *)param;
	if (keysym == KEY_PAGE_UP && fdf_g->map->z_divisor > 0.1)
		fdf_g->map->z_divisor -= 0.1;
	else if (keysym == KEY_PAGE_DOWN)
		fdf_g->map->z_divisor += 0.1;
	reset_print_amod(param);
}

static void	rotation(int keysym, void *param)
{
	t_fdf_win_g	*fdf_g;

	fdf_g = (t_fdf_win_g *)param;
	if (keysym == KEY_W || keysym == KEY_A)
		g_rotation(keysym, KEY_W, &(fdf_g->map->angle_x));
	else if (keysym == KEY_S || keysym == KEY_D)
		g_rotation(keysym, KEY_S, &(fdf_g->map->angle_y));
	else if (keysym == KEY_Q || keysym == KEY_E)
		g_rotation(keysym, KEY_Q, &(fdf_g->map->angle_z));
	reset_print_amod(param);
}

int	handle_keypress(int keysym, void *param)
{
	if (keysym == KEY_ESC)
		exit_program(param);
	else if (keysym == KEY_R)
		reset_map(param);
	else if (keysym == KEY_DIR_UP || keysym == KEY_DIR_DOWN
		|| keysym == KEY_DIR_LEFT || keysym == KEY_DIR_RIGHT)
		translate_map(keysym, param);
	else if (keysym == KEY_PAGE_UP || keysym == KEY_PAGE_DOWN)
		relief_change(keysym, param);
	else if (keysym == KEY_A || keysym == KEY_D || keysym == KEY_W
		|| keysym == KEY_S || keysym == KEY_Q || keysym == KEY_E)
		rotation(keysym, param);
	else if (keysym == KEY_K || keysym == KEY_L)
		shear_map(keysym, param);
	else if (keysym == KEY_P || keysym == KEY_I)
		parallel_projection(keysym, param);
	return (0);
}
