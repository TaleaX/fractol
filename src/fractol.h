/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:24:48 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/07 16:30:51 by tdehne           ###   ########.fr       */
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
#include <stdlib.h>
#include <stdio.h>
#include "../mlx_new/include/MLX42/MLX42.h"

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
	mlx_image_t	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_vars {
	mlx_t	*mlx;
}				t_vars;

typedef struct	s_graphic_vars {
	int		win_height;
	int		win_width;
	int		count;
	float	zoom;
	float	x_start;
	float	y_start;
}				t_graphic_vars;

typedef struct	s_pxl_data {
	int	counter;
	int px;
	int	py;
}				t_pxl_data;

void	img_pix_put(t_img *img, int x, int y, int color);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		color(int n, int max_value, double width, double offset, int reverse);
void	make_mandel(t_pxl_data *pxl, t_graphic_vars *g_vars);
void	make_julia(t_vars *vars, t_img *img);

#endif