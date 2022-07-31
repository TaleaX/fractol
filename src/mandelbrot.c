/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:31:26 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/30 20:29:10 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*void calc_mandel(t_mandel *mandel, int px, int py, t_pxl_data *pxl)
{
	double	re;
	double	im;
	int counter;

	counter = 0;
	while (1)
	{
		re = mandel->z_r * mandel->z_r - mandel->z_i * mandel->z_i + mandel->c_r;
		im = 2 * mandel->z_r * mandel->z_i + mandel->c_i;
		if (counter == 50){
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
		mandel->z_r = re;
		mandel->z_i = im;
		counter++;
	}
}

void	make_mandel(t_pxl_data *pxl, t_graphic_vars *g_vars, t_vars *vars, t_mandel *mandel)
{
	float	tmp_wy;
	float	tmp_wx;

	g_vars->steps_x =  4.0 * g_vars->zoom / vars->win_width;
	g_vars->steps_y = 4.0 * g_vars->zoom / vars->win_height;
	g_vars->w_x = - (4.0 * g_vars->zoom / 2)  + g_vars->offset_x;
	tmp_wx = g_vars->w_x;
	for (int i = 0; i < vars->win_width; i++)
	{
		g_vars->w_y = (4.0 * g_vars->zoom) / 2 + g_vars->offset_y;
		tmp_wy = g_vars->w_y;
		for (int j = 0; j < vars->win_height; j++)
		{
			mandel->c_i = g_vars->w_y;
			mandel->c_r = g_vars->w_x;
			mandel->z_i = 0.0;
			mandel->z_r = 0.0;
			calc_mandel(mandel, i, j, pxl);
			g_vars->w_y -= g_vars->steps_y;
			pxl++;
		}
		g_vars->w_x += g_vars->steps_x;
	}
	pxl->px = -1;
	g_vars->w_y = tmp_wy;
	g_vars->w_x = tmp_wx;
}*/
/*g_vars->steps_x =  4.0 / (vars->win_width + 4.0 * g_vars->zoom);
	g_vars->steps_y = 4.0  / (vars->win_height + 4.0 * g_vars->zoom);
	g_vars->w_x = - 4.0 * (1 - g_vars->zoom) / 2  + g_vars->offset_x;*/


void calc_mandel(t_pxl_data *pxl)
{
	double	re;
	double	im;
	float	z_r;
	float	z_i;
	float	c_r;
	float	c_i;
	int 	counter;

	counter = 0;
	c_r = pxl->wx;
	c_i = pxl->wy;
	z_r = 0.0;
	z_i = 0.0;
	while (1)
	{
		re = z_r * z_r - z_i * z_i + c_r;
		im = 2 * z_r * z_i + c_i;
		if (counter == ITER_DEPTH){
			pxl->counter = counter;
			pxl->recalc = 0;
			break;
		}
		if (re*re + im*im > 4.0){
			pxl->counter = counter;
			pxl->recalc = 1;
			break ;
		}
		z_r = re;
		z_i = im;
		counter++;
	}
	
}

/*void	make_mandel(t_pxl_data *pxl, t_graphic_vars *g_vars, t_vars *vars, t_mandel *mandel, t_all_s *all_s)
{
	for (g_vars->s_x = 0; g_vars->s_x < vars->win_width; g_vars->s_x++)
	{
		for (g_vars->s_y = 0; g_vars->s_y < vars->win_height; g_vars->s_y++)
		{
			screen_to_world(&g_vars->w_x, &g_vars->w_y, g_vars->s_x, g_vars->s_y, all_s->g_vars);
			if (g_vars->s_x == 0 && g_vars->s_y == 0 || g_vars->s_x == vars->win_width && g_vars->s_y == vars->win_width)
				printf("%lf %lf\n", g_vars->w_x, g_vars->w_y);
			
			pxl->wx = g_vars->w_x;
			pxl->wy = g_vars->w_y;
			pxl->px = g_vars->s_x;
			pxl->py = g_vars->s_y;
			calc_mandel(pxl);
			pxl++;
		}
	}
	pxl->px = -1;
}*/

void	make_mandel(t_pxl_data *pxl, t_graphic_vars *g_vars, t_vars *vars, t_mandel *mandel, t_all_s *all_s)
{
	g_vars->steps_x = g_vars->delta_re / vars->win_width;
	//g_vars->steps_y = g_vars->delta_im / vars->win_height;
	for (g_vars->s_x = 0; g_vars->s_x < vars->win_width; g_vars->s_x++)
	{
		for (g_vars->s_y = 0; g_vars->s_y < vars->win_height; g_vars->s_y++)
		{	
			pxl->wx = g_vars->re_min + (g_vars->s_x * g_vars->steps_x);
			pxl->wy = g_vars->im_max - (g_vars->s_y * g_vars->steps_x);
			pxl->px = g_vars->s_x;
			pxl->py = g_vars->s_y;
			calc_mandel(pxl);
			pxl++;
		}
	}
}