/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:32:08 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/17 19:19:40 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*void calc_julia(double z_r, double z_i, double c_r, double c_i, int px, int py, int depth, t_img *img, int *count)
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
}*/

void calc_julia(t_mandel *mandel, t_graphic_vars *g_vars, t_pxl_data *pxl)
{
	double	re;
	double	im;
	int counter;

	counter = 0;
	while (1)
	{
		re = mandel->z_r * mandel->z_r - mandel->z_i * mandel->z_i + mandel->c_r;
		im = 2 * mandel->z_r * mandel->z_i + mandel->c_i;
		if (counter == ITER_DEPTH){
			pxl->counter = counter;
			pxl->px = g_vars->s_x;
			pxl->py = g_vars->s_y;
			break;
		}
		if (re*re + im*im > 4.0){
			pxl->counter = counter;
			pxl->px = g_vars->s_x;
			pxl->py = g_vars->s_y;
			break ;
		}
		mandel->z_r = re;
		mandel->z_i = im;
		counter++;
	}
}

/*void	make_julia(t_vars *vars, t_img *img)
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
}*/

void	make_julia(t_pxl_data *pxl, t_graphic_vars *g_vars, t_vars *vars, t_mandel *mandel, t_all_s *all_s)
{
	float	tmp_wy;
	float	tmp_wx;
	int		sx_start;
	int		sy_start;

	for (g_vars->s_x = 0; g_vars->s_x < vars->win_width; g_vars->s_x++)
	{
		for (g_vars->s_y = 0; g_vars->s_y < vars->win_height; g_vars->s_y++)
		{
			screen_to_world(&g_vars->w_x, &g_vars->w_y, g_vars->s_x, g_vars->s_y, all_s->g_vars);
			mandel->z_i = g_vars->w_y;
			mandel->z_r = g_vars->w_x;
			calc_julia(mandel, g_vars, pxl);
			pxl++;
		}
	}
	pxl->px = -1;
}