/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 02:02:56 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/06 14:58:15 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_dot    *get_dot(char *line, int i, int width)
{
    char    **splits_line;
    t_dot   *dots;
    int     j;

    j = 0;
    find_n(line);
    splits_line = ft_split(line, ' ');
    if (!splits_line)
         return (NULL);
    dots = (t_dot *)malloc(sizeof(t_dot) * width);
    if (!dots)
        return (NULL);
    while(splits_line[j])
    {
        set_dot((&dots[j]), i, j, splits_line[j]);
        j++;
    }
    ft_free_s(splits_line);
    return (dots);
}

t_dot	**get_dot_from(char *file, int *height, int *width)
{
	int     fd;
    t_dot   **dots;
    char    *line;
    int     i;

	if (!get_map_dimensions(file, height, width) || (!*height))
        return (NULL);
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (NULL);
    dots = (t_dot **)malloc(sizeof(t_dot *) * (*height));
    if (!dots)
        return (NULL);
    line = get_next_line(fd);
    i = 0;
    while (line)
    {
        dots[i] = get_dot(line, i, *width);
        if (!dots[i++])
            return (ft_free((void **)dots, i), NULL);
        free(line);
        line = get_next_line(fd);
    }
    return (dots);
}

int put_all(t_fdf_win_g *fdf_g, char *file)
{
    int     width;
    int     heigth;

    if (!set_map(file, &width, &heigth, &(fdf_g->map)))
        return (0);
    fdf_g->img = malloc(sizeof(t_img));
    if (!(fdf_g->img))
        return (0);
    fdf_g->img->img_ptr = mlx_new_image(fdf_g->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!(fdf_g->img->img_ptr))
        return (0);
    fdf_g->img->data = mlx_get_data_addr(fdf_g->img->img_ptr, &(fdf_g->img->bit_per_pixel),
            &(fdf_g->img->size_line), &(fdf_g->img->endian));
    fill_img_with_pixel_dots(&(fdf_g->img), fdf_g->map, heigth, width);
    mlx_put_image_to_window(fdf_g->mlx, fdf_g->win, fdf_g->img->img_ptr, 0, 0);
    return (1);
}

int main(int ac, char **av)
{
    t_fdf_win_g   *fdf_g;

    if (ac != 2)
        return (ft_putstr_fd("Usage : ./fdf <MAP_FILE.fdf>\n", 2), 1);
    fdf_g = (t_fdf_win_g *)malloc(sizeof(t_fdf_win_g));
    if (!fdf_g)
        return (0);
    fdf_g->mlx = mlx_init();
    if (!(fdf_g->mlx))
        return (0);
    fdf_g->win = mlx_new_window(fdf_g->mlx, WIN_WIDTH, WIN_HEIGHT, FDF_TITLE);
    if (!(fdf_g->win))
        return (0);
    if (!put_all(fdf_g, av[1]))
        return (1);
    mlx_hook(fdf_g->win, 2, 1L << 0, (int (*)())handle_keypress, fdf_g);
    mlx_loop(fdf_g->mlx);
	return (0);
}
