/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:30:21 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/11 15:45:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup(t_fdf_win_g *fdf_g)
{
	if (!fdf_g)
		return ;
	if (fdf_g->map)
	{
		ft_free((void **)fdf_g->map->dots, fdf_g->map->height);
		ft_free((void **)fdf_g->map->proj_dots, fdf_g->map->height);
		free(fdf_g->map);
	}
	if (fdf_g->img)
	{
		mlx_destroy_image(fdf_g->mlx, fdf_g->img->img_ptr);
		free(fdf_g->img);
	}
	if (fdf_g->win)
		mlx_destroy_window(fdf_g->mlx, fdf_g->win);
	if (fdf_g->mlx)
	{
		mlx_destroy_display(fdf_g->mlx);
		free(fdf_g->mlx);
	}
	free(fdf_g);
}

void	exit_program(void *param)
{
	cleanup((t_fdf_win_g *)param);
	exit(EXIT_SUCCESS);
}

void	transform_and_project(t_dot dot, t_map *map, int *proj_x, int *proj_y)
{
	double	x;
	double	y;
	double	z;
	double	px;
	double	py;

	x = dot.abscissa;
	y = dot.ordinate;
	z = dot.altitude;
	z /= map->z_divisor;
	x -= map->width / 2;
	y -= map->height / 2;
	x += y * map->shear_factor;
	rotate(*map, &x, &y, &z);
	px = x;
	py = y;
	if (map->projection_type == 0)
	{
		px = (x - y) * cos(0.523599);
		py = -z + (x + y) * sin(0.523599);
	}
	*proj_x = (int)((px * map->zoom) + map->offset_x + map->trans.trans_x);
	*proj_y = (int)((py * map->zoom) + map->offset_y + map->trans.trans_y);
}

void	g_rotation(int keysym, int n_keysym, double *angle)
{
	if (keysym == n_keysym)
		*angle += 0.5;
	else
		*angle -= 0.5;
}

void	shear_map(int keysym, void *param)
{
	t_fdf_win_g	*fdf_g;

	fdf_g = (t_fdf_win_g *)param;
	if (keysym == KEY_K)
		fdf_g->map->shear_factor += 0.1;
	else
		fdf_g->map->shear_factor -= 0.1;
	reset_print_amod(param);
}

void	parallel_projection(int keysym, void *param)
{
	t_fdf_win_g	*fdf_g;

	fdf_g = (t_fdf_win_g *)param;
	if (keysym == KEY_I)
		fdf_g->map->projection_type = 0;
	else
		fdf_g->map->projection_type = 1;
	fdf_g->map->limits = get_map_limits(fdf_g->map);
	set_offset(fdf_g->map, fdf_g->map->limits);
	reset_print_amod(param);
}