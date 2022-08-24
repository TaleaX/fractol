/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_world_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:45:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/24 14:57:07 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	screen_to_world(t_graphic_vars *g_vars)
{
	g_vars->w_x = (double)(g_vars->s_x * g_vars->steps_x - g_vars->offset_x);
	g_vars->w_y = (double)(g_vars->offset_y - g_vars->s_y * g_vars->steps_y);
}
