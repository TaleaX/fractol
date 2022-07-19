/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_world_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:45:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/19 12:46:54 by tdehne           ###   ########.fr       */
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

void	screen_to_world(double *w_x, double *w_y, int s_x, int s_y, t_graphic_vars *g_vars)
{
	*w_x = (double)((s_x + g_vars->zoom_x * g_vars->m_sx - g_vars->m_sx) / (g_vars->def_scale_x * g_vars->zoom_x) - g_vars->offset_x);
	*w_y = (double)(g_vars->offset_y - (s_y + g_vars->zoom_y * g_vars->m_sy - g_vars->m_sy) / (g_vars->def_scale_y * g_vars->zoom_y));
		
}