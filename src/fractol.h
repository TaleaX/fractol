/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:24:48 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/24 18:00:09 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define ERROR -1
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../mlx_new/include/MLX42/MLX42.h"
#include "libft.h"

typedef	enum s_frac_type {
	MANDEL,
	JULIA,
	BSHIP
}	t_frac_type;

typedef struct	s_img {
	mlx_image_t	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_vars {
	mlx_t	*mlx;
	int		win_height;
	int		win_width;
	int		iter_depth;
	int		color_width;
	int		color_offset;
	int		color_reverse;
}				t_vars;

typedef struct	s_graphic_vars {
	int		count;
	double	offset_x;
	double	offset_y;
	double	steps_x;
	double	steps_y;
	double	w_x;
	double	w_y;
	int		s_x;
	int		s_y;
}				t_graphic_vars;

typedef struct	s_pxl_data {
	int		counter;
	int		px;
	int		py;
	double	wx;
	double	wy;
}				t_pxl_data;

typedef struct s_fractals {
	double		z_r;
	double		z_i;
	double		c_r;
	double		c_i;
	t_frac_type	frac_type;
} t_fractals;

typedef struct s_all_s t_all_s;

typedef void	(*t_calc) (t_pxl_data *pxl, t_all_s *all_s);

struct s_all_s {
	t_graphic_vars 	*g_vars;
	t_pxl_data 		*pxl;
	t_vars			*vars;
	t_img			*img;
	t_fractals		*fractal;
	t_calc			*calc;
};


void	img_pix_put(t_img *img, int x, int y, int color);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
//coloring
int		color(int n, int max_value, double width, double offset, int reverse);
void	make_mandel(t_pxl_data *pxl, t_all_s *all_s);
void	make_julia(t_pxl_data *pxl, t_all_s *all_s);
void	screen_to_world(t_graphic_vars *g_vars);
void	make_bship(t_pxl_data *pxl, t_all_s *all_s);

//init
int		init_vars(t_all_s all_s, char **argv);
int		get_fractal_type(char **argv);

#endif