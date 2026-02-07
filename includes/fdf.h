/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:51:23 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/07 20:35:41 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define FDF_TITLE "titre du project"
# define COLOR_DISCO 0x9A1F6A
# define COLOR_BRICK 0xC2294E
# define COLOR_FLAMINGO 0xEC4B27
# define COLOR_JAFFA 0xEF8633
# define COLOR_SAFFRON 0xF3AF3D
# define COLOR_BLACK 0x000000
# define KEY_ESC 65307
# define KEY_R 114
# define KEY_DIR_UP 65362
# define KEY_DIR_DOWN 65364
# define KEY_DIR_LEFT 65361
# define KEY_DIR_RIGHT 65363
# define KEY_ZOOM_P 65451
# define KEY_ZOOM_M 65453
# define KEY_W 119
# define KEY_A 97
# define KEY_Q 113
# define KEY_S 115
# define KEY_D 100
# define KEY_E 101
# define KEY_I 105
# define KEY_P 112
# define KEY_PAGE_UP 65365
# define KEY_PAGE_DOWN 65366
# define KEY_K 107
# define KEY_L 108

typedef struct s_dot
{
	double	abscissa;
	double	ordinate;
	double	altitude;
	int		color;
}	t_dot;

typedef struct s_img
{
	void	*img_ptr;
	char	*data;
	int		bit_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_proj_dot
{
	double	proj_x;
	double	proj_y;
	int		color;
}	t_proj_dot;

typedef struct s_limits
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
}	t_limits;

typedef struct s_map
{
	int			height;
	int			width;
	int			zoom;
	double		z_divisor;
	float		offset_x;
	float		offset_y;
	t_dot		**dots;
	t_proj_dot	**proj_dots;
	double		angle_x;
	double		angle_y;
	double		angle_z;
	int			projection_type;
	double		shear_factor;
	t_limits	limits;
}	t_map;

typedef	struct s_fdf_win_g
{
	t_map	*map;
	t_img	*img;
	void	*mlx;
	void	*win;
}	t_fdf_win_g;

t_dot		**get_dot_from(char *file, int *height, int *width);
void		fill_img_with_pixel_dots(t_img **img, t_map *map,
				int height, int width);
int			put_all(t_fdf_win_g *fdf_g, char *file);
int			get_map_dimensions(char *file, int *width, int *height);
void		set_dot(t_dot *dot, int i, int j, char *element);
void		ft_free(void **table, int size);
t_limits	get_map_limits(t_map *map);
int			inits_map(char *file, int *width, int *height, t_map **map);
void		draw_lign(t_img *img, t_proj_dot dot_a, t_proj_dot dot_b);
void		rotate_x(t_map **map);
void		rotate_y(t_map **map);
void		rotate_z(t_map **map);
void		iso_project(t_dot dot, double *proj_x,
				double *proj_y, double z_divisor);
void		print_map_debug(t_map *map);
int			ft_atoi_hex(char *str);
int			get_color(int start, int end, double percentage);
void		ft_free_s(char **table);
void		find_n(char *line);
void		clear_image(t_img *img);
void		exit_program(void *param);
int			handle_keypress(int keysym, void *param);
int			init_proj_dots(t_map *map);
void		set_zoom(t_map *map, t_limits lim);
void		set_initial_factor(t_map *map);
void		set_offset(t_map *map, t_limits lim);
void		reset_print_amod(void *param);
int			handle_mouse(int button, int x, int y, void *param);
void		g_rotation(int keysym, int n_keysym, double *angle);

#endif
