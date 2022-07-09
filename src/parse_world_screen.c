/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_world_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:45:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/09 18:08:51 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	world_to_screen(t_graphic_vars *g_vars)
{
	g_vars->s_x = (g_vars->w_x + g_vars->offset_x) / g_vars->steps_x;
	g_vars->s_y = (g_vars->offset_y - g_vars->w_y) / g_vars->steps_y;
}

void	screen_to_world(t_graphic_vars *g_vars, t_vars *vars)
{
	g_vars->w_x = g_vars->s_x * g_vars->steps_x - g_vars->offset_x;
	g_vars->w_y = (g_vars->s_y < vars->win_height / 2) ? g_vars->offset_y - g_vars->s_y * g_vars->steps_y : - (g_vars->s_y * g_vars->steps_y - g_vars->offset_y);
}