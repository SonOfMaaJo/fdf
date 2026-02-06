/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 02:02:56 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/06 10:10:28 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_dot    *get_dot(char *line, int i, int width)
{
    char    **splits_line;
    t_dot   *dots;
    int     j;

    j = 0;
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
    ft_free((void **)splits_line, j);
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

int inits(void **mlx, void **win, t_img **img, char *file, t_map **map)
{
    int     width;
    int     heigth;

    if (!set_map(file, &width, &heigth, map))
        return (0);
    *img = malloc(sizeof(t_img));
    if (!(*img))
        return (0);
    (*img)->img_ptr = mlx_new_image(*mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!((*img)->img_ptr))
        return (0);
    (*img)->data = mlx_get_data_addr((*img)->img_ptr, &((*img)->bit_per_pixel),
            &((*img)->size_line), &((*img)->endian));
    fill_img_with_pixel_dots(img, *map, heigth, width);
    mlx_put_image_to_window(*mlx, *win, (*img)->img_ptr, 0, 0);
    return (1);
}

int main(int ac, char **av)
{
    void    *mlx;
    void    *win;
    t_img   *img;
    t_map   *map;

    if (ac != 2)
        return (ft_putstr_fd("Usage : ./fdf <MAP_FILE.fdf>\n", 2), 1);
    mlx = mlx_init();
    if (!(mlx))
        return (0);
    win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, FDF_TITLE);
    if (!(win))
        return (0);
    if (!inits(&mlx, &win, &img, av[1], &map))
        return (1);
    mlx_loop(mlx);
	return (0);
}
