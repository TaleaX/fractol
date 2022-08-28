/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:45:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/28 17:07:35 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	screen_to_world(t_graphic_vars *g_vars)
{
	g_vars->w_x = (double)(g_vars->s_x * g_vars->steps_x - g_vars->offset_x);
	g_vars->w_y = (double)(g_vars->offset_y - g_vars->s_y * g_vars->steps_y);
}

void	init_calc(t_calc calc[3])
{
	calc[0] = make_mandel;
	calc[1] = make_julia;
	calc[2] = make_bship;
}
