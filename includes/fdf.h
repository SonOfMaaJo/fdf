/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:51:23 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/05 13:44:42 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <fcntl.h>

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define FDF_TITLE "titre du project"
# define COLOR_DISCO 0x9A1F6A
# define COLOR_BRICK 0xC2294E
# define COLOR_FLAMINGO 0xEC4B27
# define COLOR_JAFFA 0xEF8633
# define COLOR_SAFFRON 0xF3AF3D

typedef struct s_dot
{
    int abscissa;
    int ordinate;
    int altitude;
    int color;
}   t_dot;

typedef struct s_camera
{
    double alpha;
    double beta;
    double gamma;
}   t_camera;

typedef struct s_img
{
    void    *img_ptr;
    char    *data;
    int     bit_per_pixel;
    int     size_line;
    int     endian;
}   t_img;

typedef struct s_proj_dot
{
    int proj_x;
    int proj_y;
    int color;
}   t_proj_dot;

typedef struct s_map
{
    int         height;
    int         width;
    int         zoom;
    float       offset_x;
    float       offset_y;
    t_dot       **dots
    t_limits    limits;
}   t_map;

typedef struct s_limits
{
    int min_x;
    int max_x;
    int min_y;
    int max_y;
}   t_limits;

t_dot	    **get_dot_from(char *file, int *height, int *width);
void        fill_img_with_pixel_dots(t_img **img, t_map map, int h, int w);
int         inits(void **mlx, void **win, t_img **img, char *file);
int         get_map_dimensions(char *file, int *width, int *height);
void        set_dot(t_dot *dot, int i, int j, char *element);
void        ft_free(void **table, int size);
t_limits    get_map_limits(t_map *map);
int         set_map(char *file, int *width, int *height, t_dot **map);
void        draw_lign(t_img *img, t_proj_dot dot_a, t_proj_dot dot_b);
void        rotate_x(double *y, double *z, double alpha);
void        rotate_y(double *x, double *z, double beta);
void        rotate_z(double *x, double *y, double gamma);
void        translation(double *x, double *y, double *z, double k);
void        iso_project(t_dot dot, double *proj_x, double *proj_y);
int         ft_atoi_hex(char *str);

#endif
