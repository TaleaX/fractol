/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:24:48 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/30 14:33:49 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define ITER_DEPTH 100
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../mlx_new/include/MLX42/MLX42.h"

# define ABS(num) (num < 0 ? num * - 1 : num)

typedef struct s_mandel {
	float	c_r;
	float	c_i;
	float	z_r;
	float	z_i;
}	t_mandel;

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
}				t_vars;

typedef struct	s_graphic_vars {
	int		count;
	double	zoom_x;
	double	zoom_y;
	double	def_scale_x;
	double	def_scale_y;
	double	offset_x;
	double	offset_y;
	double	steps_x;
	double	steps_y;
	double	w_x;
	double	w_y;
	double	m_wx_start;
	double	m_wy_start;
	int		s_x;
	int		s_y;
	int		m_sy;
	int		m_sx;
	double	delta_re;
	double	delta_im;
	double	re_max;
	double	re_min;
	double	im_max;
	double	im_min;
	double	step_size;

}				t_graphic_vars;

typedef struct	s_pxl_data {
	int		counter;
	int		px;
	int		py;
	float	wx;
	float	wy;
	int		recalc;
}				t_pxl_data;

typedef struct s_all_s {
	t_graphic_vars 	*g_vars;
	t_pxl_data 		*pxl;
	t_vars			*vars;
	t_img			*img;
	t_mandel		*mandel;
} t_all_s;

void	img_pix_put(t_img *img, int x, int y, int color);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		color(int n, int max_value, double width, double offset, int reverse);
void	make_mandel(t_pxl_data *pxl, t_graphic_vars *g_vars, t_vars *vars, t_mandel *mandel, t_all_s *all_s);
void	make_julia(t_pxl_data *pxl, t_graphic_vars *g_vars, t_vars *vars, t_mandel *mandel, t_all_s *all_s);
//void	make_mandel(t_all_s *all_s);
//void	make_julia(t_vars *vars, t_img *img);
//void	screen_to_world(t_graphic_vars *g_vars, t_vars *vars);
//void	world_to_screen(t_graphic_vars *g_vars);
void	world_to_screen(int *s_x, int *s_y, double w_x, double w_y, t_graphic_vars *g_vars);
void	screen_to_world(double *w_x, double *w_y, int s_x, int s_y, t_graphic_vars *g_vars);

void	recalculate(t_pxl_data *pxl);

#endif