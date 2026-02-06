/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyb_mouse_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:07:18 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/06 14:46:44 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keypress(int keysym, void *param)
{
	if (keysym == KEY_ESC)
		exit_program(param);
	return (0);
}

