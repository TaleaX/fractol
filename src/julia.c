/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:32:08 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/24 18:01:28 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void calc_julia(t_pxl_data *pxl, t_all_s *all_s)
{
	double	re;
	double	im;
	int counter;

	counter = 0;
	while (1)
	{
		re = all_s->fractal->z_r * all_s->fractal->z_r - all_s->fractal->z_i * all_s->fractal->z_i + all_s->fractal->c_r;
		im = 2 * all_s->fractal->z_r * all_s->fractal->z_i + all_s->fractal->c_i;
		if (counter == all_s->vars->iter_depth){
			pxl->counter = counter;
			pxl->px = all_s->g_vars->s_x;
			pxl->py = all_s->g_vars->s_y;
			break;
		}
		if (re*re + im*im > 4.0){
			pxl->counter = counter;
			pxl->px = all_s->g_vars->s_x;
			pxl->py = all_s->g_vars->s_y;
			break ;
		}
		all_s->fractal->z_r = re;
		all_s->fractal->z_i = im;
		counter++;
	}
}

void	make_julia(t_pxl_data *pxl, t_all_s *all_s)
{
	float	tmp_wy;
	float	tmp_wx;
	int		sx_start;
	int		sy_start;

	for (all_s->g_vars->s_x = 0; all_s->g_vars->s_x < all_s->vars->win_width; all_s->g_vars->s_x++)
	{
		for (all_s->g_vars->s_y = 0; all_s->g_vars->s_y < all_s->vars->win_height; all_s->g_vars->s_y++)
		{
			screen_to_world(all_s->g_vars);
			all_s->fractal->z_i = all_s->g_vars->w_y;
			all_s->fractal->z_r = all_s->g_vars->w_x;
			calc_julia(pxl, all_s);
			pxl++;
		}
	}
	pxl->px = -1;
}
