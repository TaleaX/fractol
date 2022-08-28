/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:31:23 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/28 17:07:30 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_color_vars(t_all_s *all_s, char **argv)
{
	all_s->fractal->frac_type = get_fractal_type(argv);
	all_s->vars->iter_depth = 50;
	all_s->vars->color_offset = 0;
	all_s->vars->color_width = 5;
	all_s->vars->color_reverse = 0;
	all_s->color->shift = 0;
	all_s->color->max_value = 50;
	all_s->color->dynamic_max = 0;
	if (all_s->fractal->frac_type == MANDEL
		|| all_s->fractal->frac_type == JULIA)
		all_s->color->shift = 1;
}

static void	init_g_vars(t_all_s *all_s)
{
	all_s->g_vars->count = 1;
	all_s->g_vars->w_x = 0.0;
	all_s->g_vars->w_y = 0.0;
	all_s->vars->win_height = 600;
	all_s->vars->win_width = 600;
	all_s->g_vars->offset_x = 2;
	all_s->g_vars->offset_y = 2;
	all_s->g_vars->steps_x = 4.0 / all_s->vars->win_width;
	all_s->g_vars->steps_y = 4.0 / all_s->vars->win_height;
}

static void	init_pxl_vars(t_all_s *all_s)
{
	all_s->pxl->counter = 0;
	all_s->pxl->px = 0;
	all_s->pxl->py = 0;
	all_s->pxl->wx = 0.0;
	all_s->pxl->wy = 0.0;
}

static void	init_mlx(t_all_s *all_s)
{
	if (all_s->fractal->frac_type == ERROR)
	{
		all_s->vars->mlx = NULL;
		return ;
	}
	all_s->vars->mlx = mlx_init(all_s->vars->win_width, \
		all_s->vars->win_height, "FRACTOL", 0);
	all_s->img->img = mlx_new_image(all_s->vars->mlx, \
		all_s->vars->win_width, all_s->vars->win_height);
}

int	init_vars(t_all_s *all_s, char **argv)
{
	t_img			*img;
	t_vars			*vars;
	t_fractals		*fractal;
	t_graphic_vars	*g_vars;
	t_color			*color;

	img = (t_img *)malloc(sizeof(t_img));
	vars = (t_vars *)malloc(sizeof(t_vars));
	g_vars = (t_graphic_vars *)malloc(sizeof(t_graphic_vars));
	fractal = (t_fractals *)malloc(sizeof(t_fractals));
	color = (t_color *)malloc(sizeof(t_color));
	all_s->img = img;
	all_s->vars = vars;
	all_s->g_vars = g_vars;
	all_s->fractal = fractal;
	all_s->color = color;
	init_color_vars(all_s, argv);
	init_g_vars(all_s);
	init_pxl_vars(all_s);
	init_mlx(all_s);
	return (all_s->fractal->frac_type);
}
