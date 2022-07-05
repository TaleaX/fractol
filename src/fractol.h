/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:24:48 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/05 13:26:16 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define MAGENTA 0x00FF00FF
# define RED 0x00d44275
# define PURPLE 0x00c034eb
# define BLUE 0x004e42d4
# define LIGHT_BLUE 0x0042cad4
# define LIGHT_PURPLE 0x00288f2
# define ROSA 0x00e58feb
#include <math.h>
#include "mlx.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		win_height;
	int		win_width;
	int		count;
	float	zoom;
}				t_vars;

typedef struct	s_pxl_data {
	int	counter;
	int px;
	int	py;
}				t_pxl_data;

void	img_pix_put(t_img *img, int x, int y, int color);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		color(int n, int max_value, double width, double offset, int reverse);
void	calc_mandel(double c_r, double c_i, double z_r, double z_i, int px, int py, int depth, t_img *img, int *count);
void	make_mandel(t_vars *vars, t_img *img);
void	make_julia(t_vars *vars, t_img *img);

#endif