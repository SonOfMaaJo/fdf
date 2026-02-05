/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:28:04 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/05 19:05:49 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(int start, int end, double percentage)
{
	int	r;
	int	g;
	int	b;

	r = get_light((start >> 16) & 0xFF, (end >> 16) & 0xFF, percentage);
	g = get_light((start >> 8) & 0xFF, (end >> 8) & 0xFF, percentage);
	b = get_light(start & 0xFF, end & 0xFF, percentage);
	return ((r << 16) | (g << 8) | b);
}
