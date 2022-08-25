/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:31:23 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/25 17:02:51 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_fractal_type(char **argv)
{
	if (!*(argv + 1))
		return (ERROR);
	else if (ft_strncmp(*(argv + 1), "mandel", 6) == 0)
		return (MANDEL);
	else if (ft_strncmp(*(argv + 1), "julia", 5) == 0)
		return (JULIA);
	else if (ft_strncmp(*(argv + 1), "bship", 5) == 0)
		return (BSHIP);
	return (ERROR);
}

int	init_vars(t_all_s all_s, char **argv)
{
	all_s.g_vars->count = 1;
	all_s.g_vars->w_x = 0.0;
	all_s.g_vars->w_y = 0.0;
	all_s.vars->win_height = 600;
	all_s.vars->win_width = 600;
	all_s.g_vars->offset_x = 2;
	all_s.g_vars->offset_y = 2;
	all_s.g_vars->steps_x = 4.0 / all_s.vars->win_width;
	all_s.g_vars->steps_y = 4.0 / all_s.vars->win_height;
	all_s.vars->iter_depth = 50;
	all_s.vars->color_offset = 0;
	all_s.vars->color_width = 5;
	all_s.vars->color_reverse = 0;
	all_s.pxl->counter = 0;
	all_s.pxl->px = 0;
	all_s.pxl->py = 0;
	all_s.pxl->wx = 0.0;
	all_s.pxl->wy = 0.0;
	all_s.fractal->frac_type = get_fractal_type(argv);
	all_s.vars->mlx = mlx_init(all_s.vars->win_width, \
		all_s.vars->win_height, "FRACTOL", 0);
	all_s.img->img = mlx_new_image(all_s.vars->mlx, \
		all_s.vars->win_width, all_s.vars->win_height);
	return (all_s.fractal->frac_type);
}
