/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:12:00 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/28 16:56:17 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_exit(t_all_s all_s)
{
	free(all_s.pxl);
	free(all_s.fractal);
	free(all_s.color);
	free(all_s.g_vars);
	free(all_s.img);
	if (all_s.vars->mlx)
		mlx_terminate(all_s.vars->mlx);
	free(all_s.vars);
	all_s.pxl = NULL;
	all_s.g_vars = NULL;
	all_s.fractal = NULL;
	all_s.vars = NULL;
	all_s.img = NULL;
	system("leaks fractol");
	exit(0);
}

void	zoom_util(double ydelta, t_all_s *all_s)
{
	if (ydelta > 0)
	{
		all_s->g_vars->steps_x *= 0.9;
		all_s->g_vars->steps_y *= 0.9;
	}
	else
	{
		all_s->g_vars->steps_x *= 1.1;
		all_s->g_vars->steps_y *= 1.1;
	}
}

void	set_julia_vals(t_all_s all_s, char **argv)
{
	all_s.fractal->c_r = ft_atof(argv[2]);
	all_s.fractal->c_i = ft_atof(argv[3]);
}

void	reset(t_all_s all_s)
{
	all_s.vars->iter_depth = 50;
	all_s.vars->color_offset = 0;
	all_s.vars->color_width = 5;
	all_s.vars->color_reverse = 0;
	all_s.g_vars->offset_x = 2;
	all_s.g_vars->offset_y = 2;
	all_s.g_vars->steps_x = 4.0 / all_s.vars->win_width;
	all_s.g_vars->steps_y = 4.0 / all_s.vars->win_height;
	all_s.fractal->c_r = -0.752;
	all_s.fractal->c_i = 0.152;
	all_s.color->max_value = 50;
	all_s.color->dynamic_max = 0;
	all_s.color->shift = 0;
	if (all_s.fractal->frac_type == MANDEL || all_s.fractal->frac_type == JULIA)
		all_s.color->shift = 1;
}

t_frac_type	get_fractal_type(char **argv)
{
	if (!*(argv + 1))
		return (ERROR);
	else if (ft_strncmp(*(argv + 1), "mandel", 6) == 0)
		return (MANDEL);
	else if (ft_strncmp(*(argv + 1), "julia", 5) == 0 && argv[2] && argv[3])
		return (JULIA);
	else if (ft_strncmp(*(argv + 1), "bship", 5) == 0)
		return (BSHIP);
	return (ERROR);
}
