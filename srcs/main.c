/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 02:02:56 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/31 19:32:40 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot	*get_dot_from(int fd, int *height, int *witdh)
{
	(void)height;
	(void)witdh;
	if (fd)
		return (NULL);
	return (NULL);
}


void    *inits(void **mlx, void  **win, void **img, int fd)
{
    void    *ptr;
    t_dot   *dots;
    int     witdh;
    int     heigth;

    *mlx = mlx_init();
    if (!(*mlx))
        return (NULL);
    win = mlx_new_window(*mlx, WIN_SX, WIN_SY, FDF_TITLE);
    if (!win)
        return (NULL);
    dots = get_dot_from_file(fd, &heigth, &witdh);
    if (!dots)
        return (NULL);
    (*img)->img_ptr = mlx_new_image(*mlx, heigth, witdh);
    if (!((*img)->img_ptr))
        return (NULL);
    img->data = mlx_get_data_addr(img->img_ptr, img->bit_per_pixel,
            img->size_len, img->endian);
    fill_img_with_pixel_dots(img, dots);
    return (dots);
}

int main(int ac, char **av)
{
    void    *mlx;
    void    *win;
    t_img   *img;
    t_dot   **dots;
    int     fd;

    if (ac != 2)
        return (write(2, "Usage : ./fdf <MAP_FILE.fdf>", 30), 1);
    fd = open(av[0], RDONLY);
    if (fd == -1)
        return (write(1, "Error : cannot open file\n", 26), 1);
    *dots = inits(&mlx, &win, &img, fd);
    close(fd);
    mlx_loop(mlx);
	return (0);
}
