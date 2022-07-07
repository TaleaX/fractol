/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:31:26 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/07 16:33:01 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void calc_mandel(double c_r, double c_i, double z_r, double z_i, int px, int py, int depth, t_pxl_data *pxl)
{
	double	re;
	double	im;
	int counter;

	counter = 0;
	while (1)
	{
		re = z_r*z_r - z_i*z_i + c_r;
		im = 2*z_r*z_i + c_i;
		if (counter == depth){
			pxl->counter = counter;
			pxl->px = px;
			pxl->py = py;
			//my_mlx_pixel_put(img, px, py, 0x00000000);
			break;
		}
		if (re*re + im*im > 4.0){
			pxl->counter = counter;
			pxl->px = px;
			pxl->py = py;
			//my_mlx_pixel_put(img, px, py, color(counter, 50, 5 * M_PI / 3 + sin(*count / 50.0) + 1, sin(*count / 50.0) + 1, 1));
			break ;
		}
		z_r = re;
		z_i = im;
		counter++;
	}
}

void	make_mandel(t_pxl_data *pxl, t_graphic_vars *g_vars)
{
	double		x_start;
	double		y_start;
	double		steps_x;
	double		steps_y;

	x_start = -2;
	steps_x =  4.0 * g_vars->zoom / g_vars->win_width;
	steps_y = 4.0 * g_vars->zoom / g_vars->win_height;
	for (int i = 0; i < g_vars->win_width; i++)
	{
		y_start = -2;
		for (int j = 0; j < g_vars->win_height; j++)
		{
			calc_mandel(x_start, y_start, 0.0, 0.0, i, j, 50, pxl);
			y_start += steps_y;
			pxl++;
		}
		x_start += steps_x;
	}
	pxl->px = -1;
}