/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:51:23 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/31 18:41:45 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# define WIN_SX 300
# define WIN_SY 300
# define IMG_SX 100
# define IMG_SY 100
# define FDF_TITLE "titre du project"

typedef struct s_dot
{
    int     abscissa_2D;
    int     ordinate_2D;
    char    *color;
}   t_dot;
typedef struct s_img
{
    void    *img_ptr;
    char    *data;
    int     *bit_per_pixel;
    int     *size_line;
    int     *endian;
}   t_img;

#endif
