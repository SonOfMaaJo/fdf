/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:30:21 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/07 20:14:04 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_program(void *param)
{
	t_fdf_win_g	*fdf_g;

	fdf_g = (t_fdf_win_g *)(param);
	ft_free((void **)(fdf_g->map)->dots, (fdf_g->map)->height);
	ft_free((void **)(fdf_g->map)->proj_dots, (fdf_g->map)->height);
	free(fdf_g->map);
	mlx_destroy_image(fdf_g->mlx, (fdf_g->img)->img_ptr);
	free(fdf_g->img);
	mlx_destroy_window(fdf_g->mlx, fdf_g->win);
	mlx_destroy_display(fdf_g->mlx);
	free(fdf_g->mlx);
	free(fdf_g);
	exit(EXIT_SUCCESS);
}

void	g_rotation(int keysym, int n_keysym, double *angle)
{
	if (keysym == n_keysym)
		*angle += 0.5;
	else
		*angle -= 0.5;
}

