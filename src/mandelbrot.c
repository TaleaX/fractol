/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:31:26 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/24 14:57:02 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void calc_mandel(t_pxl_data *pxl, t_all_s *all_s)
{
	double	re;
	double	im;
	int 	counter;

	counter = 0;
	all_s->fractal->c_r = pxl->wx;
	all_s->fractal->c_i = pxl->wy;
	all_s->fractal->z_r = 0.0;
	all_s->fractal->z_i = 0.0;
	while (1)
	{
		re = all_s->fractal->z_r * all_s->fractal->z_r - all_s->fractal->z_i * all_s->fractal->z_i + all_s->fractal->c_r;
		im = 2 * all_s->fractal->z_r * all_s->fractal->z_i + all_s->fractal->c_i;
		if (counter == all_s->vars->iter_depth){
			pxl->counter = counter;
			break;
		}
		if (re*re + im*im > 4.0){
			pxl->counter = counter;
			break ;
		}
		all_s->fractal->z_r = re;
		all_s->fractal->z_i = im;
		counter++;
	}
	
}

void	make_mandel(t_pxl_data *pxl, t_all_s *all_s)
{
	for (all_s->g_vars->s_x = 0; all_s->g_vars->s_x < all_s->vars->win_width; all_s->g_vars->s_x++)
	{
		for (all_s->g_vars->s_y = 0; all_s->g_vars->s_y < all_s->vars->win_height; all_s->g_vars->s_y++)
		{
			screen_to_world(all_s->g_vars);
			pxl->wx = all_s->g_vars->w_x;
			pxl->wy = all_s->g_vars->w_y;
			pxl->px = all_s->g_vars->s_x;
			pxl->py = all_s->g_vars->s_y;
			calc_mandel(pxl, all_s);
			pxl++;
		}
	}
	pxl->px = -1;
}
