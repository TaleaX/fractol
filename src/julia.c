/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:32:08 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/03 17:32:44 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void calc_julia(double z_r, double z_i, double c_r, double c_i, int px, int py, int depth, t_img *img, int *count)
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
			my_mlx_pixel_put(img, px, py, 0x00000000);
			break;
		}
		if (re*re + im*im > 4.0){
			my_mlx_pixel_put(img, px, py, color(counter, 50, 5 * M_PI / 3 + sin(*count) + 1, sin(*count) + 1, 0));
			break ;
		}
		
		z_r = re;
		z_i = im;
		counter++;
	}
}

void	make_julia(t_vars *vars, t_img *img)
{
	double	neg;
	double	pos;
	double	steps_x;
	double	steps_y;

	neg = -2;
	steps_x =  4.0 / vars->win_width;
	steps_y = 4.0 / vars->win_height;
	for (int i = 0; i < vars->win_width; i++)
	{
		pos = 2;
		for (int j = 0; j < vars->win_height; j++)
		{
			calc_mandel(neg, pos, -1, 0.5, i, j, 50, img, &vars->count);
			pos -= steps_y;
		}
		neg += steps_x;
	}
}