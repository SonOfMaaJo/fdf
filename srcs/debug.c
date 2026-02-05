/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini-cli <support@google.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:00:00 by gemini-cli        #+#    #+#             */
/*   Updated: 2026/02/03 14:00:00 by gemini-cli        #+#    #+#             */
/*   Updated: 2026/02/03 14:00:00 by gemini-cli        #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	print_dots_debug(t_dot **dots, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	printf("\n--- DEBUG: MAP CONTENT (%dx%d) ---\n", width, height);
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			printf("[L:%d, C:%d] -> x2D: %.2f, y2D: %.2f, Color: %s\n",
				i, j, dots[i][j].abscissa_2D, dots[i][j].ordinate_2D,
				dots[i][j].color ? dots[i][j].color : "NONE");
			j++;
		}
		i++;
	}
	printf("--- END OF DEBUG ---\n\n");
}
