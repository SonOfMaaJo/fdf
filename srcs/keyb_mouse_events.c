/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyb_mouse_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:07:18 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/06 11:15:58 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keypress(int keysym, void *param)
{
	if (keysym == KEY_ESC)
		exit_program(param);
	return (0);
}

int	handle_mouse(int buttom, int x, int y, void *param)
{
	t_map *map;

	map = (t_map *)param;
	if (button == 4)
		map->zoom += 2;
	else if (button == 5)
		map->zoom -= 2;
	render_map(map);
	return (0);
}

int	close_window(void *param)
{
	exit(0);
	return (0);
}
