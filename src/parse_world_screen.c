/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_world_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:45:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/23 14:11:29 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*void	world_to_screen(int *s_x, int *s_y, double w_x, double w_y, t_graphic_vars *g_vars)
{
	*s_x = (int)((w_x + g_vars->zoom_x * 2 - 2 + g_vars->offset_x) * g_vars->def_scale_x * g_vars->zoom_x);
	*s_y = (int)((g_vars->offset_y - w_y - g_vars->zoom_y * 2 + 2) * g_vars->def_scale_y * g_vars->zoom_y);
}

void	screen_to_world(t_graphic_vars *g_vars, t_vars *vars)
{
	g_vars->w_x = g_vars->s_x * g_vars->steps_x - g_vars->offset_x;
	g_vars->w_y = (g_vars->s_y < vars->win_height / 2) ? g_vars->offset_y - g_vars->s_y * g_vars->steps_y : - (g_vars->s_y * g_vars->steps_y - g_vars->offset_y);
}*/

/*void	screen_to_world(double *w_x, double *w_y, int s_x, int s_y, t_graphic_vars *g_vars)
{
	double	x_ratio;
	double	y_ratio;

	x_ratio = (double)(g_vars->m_sx) / 600.0;
	y_ratio = (double)(g_vars->m_sy) / 600.0;
	if (g_vars->m_sx == 0)
		x_ratio = 1.0;
	if (g_vars->m_sy == 0)
		y_ratio = 1.0;
	//printf("%lf\n", y_ratio);
	//g_vars->offset_x *= g_vars->zoom_x * x_ratio;
	//g_vars->offset_y *= g_vars->zoom_y * y_ratio;
	//+ g_vars->zoom_x * g_vars->m_sx - g_vars->m_sx
	// + g_vars->zoom_y * g_vars->m_sy - g_vars->m_sy
	*w_x = (double)((s_x + g_vars->zoom_x * g_vars->m_sx - g_vars->m_sx) / (g_vars->def_scale_x * g_vars->zoom_x) - g_vars->offset_x);
	*w_y = (double)(g_vars->offset_y - (s_y + g_vars->zoom_y * g_vars->m_sy - g_vars->m_sy) / (g_vars->def_scale_y * g_vars->zoom_y));
}*/

void	screen_to_world(t_graphic_vars *g_vars)
{

	
	
	//printf("%lf %lf %lf\n", g_vars->re_min, dd_re, g_vars->delta_re);
	
	//g_vars->def_scale_y = 600.0 / (g_vars->delta_im);
	//g_vars->def_scale_x = 600.0 / (g_vars->delta_re);
	/*g_vars->offset_x = g_vars->zoom_x * g_vars->offset_x - g_vars->offset_x;
	g_vars->offset_y = g_vars->zoom_y * g_vars->offset_y - g_vars->offset_y;
	if (g_vars->offset_x < 0)
		g_vars->offset_x *= -1;
	if (g_vars->offset_y < 0)
		g_vars->offset_y *= -1;
	*/
	//+ g_vars->zoom_x * g_vars->m_sx - g_vars->m_sx
	// + g_vars->zoom_y * g_vars->m_sy - g_vars->m_sy

	//printf("%lf %lf %lf\n", g_vars->re_min, g_vars->steps_x, g_vars->delta_re);
	
	//*w_x = (double)(s_x * g_vars->steps_x - g_vars->offset_x);
	//*w_y = (double)(g_vars->offset_y - s_y * g_vars->steps_y);
	g_vars->w_x = (double)(g_vars->s_x * g_vars->steps_x - g_vars->offset_x);
	g_vars->w_y = (double)(g_vars->offset_y - g_vars->s_y * g_vars->steps_y);
	//printf("%lf %lf\n", *w_x, *w_y);
	//*w_x = (double)((s_x) / (g_vars->def_scale_x * g_vars->zoom_x) - g_vars->offset_x * x_ratio);
	//*w_y = (double)(g_vars->offset_y * y_ratio - (s_y) / (g_vars->def_scale_y * g_vars->zoom_y));
}