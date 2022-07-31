/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:19:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/31 16:28:17 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"



void test(void *context){
	t_all_s	*all_s = context;
	t_pxl_data	*tmp;

	(all_s->g_vars->count)++;
	tmp = all_s->pxl;
	while (tmp->px != -1)
	{
		if (tmp->counter == ITER_DEPTH)
		{
			mlx_put_pixel(all_s->img->img, tmp->px, tmp->py, 0x000000FF);
		}
		else
		{
			mlx_put_pixel(all_s->img->img, tmp->px, tmp->py, color(tmp->counter, 500, 5 * M_PI / 3 + sin(all_s->g_vars->count / 20.0) + 1, sin(all_s->g_vars->count / 20.0) + 1, 1));
		}
		(tmp)++;
	}
	//mlx_get_mouse_pos(all_s->vars->mlx, &all_s->mouse_x, &all_s->mouse_y);
	//all_s->g_vars->m_sx = 300;
	//all_s->g_vars->m_sy = 300;
	mlx_image_to_window(all_s->vars->mlx, all_s->img->img, 0, 0);
}

void my_keyhook(mlx_key_data_t keydata, void* context)
{
	t_all_s	*all_s = context;
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		all_s->g_vars->offset_x += 0.2;
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		all_s->g_vars->offset_x -= 0.2;
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		all_s->g_vars->offset_y -= 0.2;
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		all_s->g_vars->offset_y += 0.2;
		
	}
	make_mandel(all_s->pxl, all_s->g_vars, all_s->vars, all_s->mandel, all_s);
}

void	zoom_math(t_all_s *all_s, int scale_dir)
{
	double	dd_re;
	double	dd_im;
	double	x_ratio;
	double	y_ratio;

	mlx_get_mouse_pos(all_s->vars->mlx, &all_s->g_vars->m_sx, &all_s->g_vars->m_sy);
	x_ratio = (double)(all_s->g_vars->m_sx) / all_s->vars->win_width;
	y_ratio = (double)(all_s->g_vars->m_sy) / all_s->vars->win_height;
	if (all_s->g_vars->m_sx == 0)
		x_ratio = 1.0;
	if (all_s->g_vars->m_sy == 0)
		y_ratio = 1.0;
	all_s->g_vars->delta_re = all_s->g_vars->re_max - all_s->g_vars->re_min;
	all_s->g_vars->delta_im = all_s->g_vars->im_max - all_s->g_vars->im_min;
	if (scale_dir == 1)
	{
		dd_re = (all_s->g_vars->zoom_x * all_s->g_vars->delta_re) - all_s->g_vars->delta_re;
		dd_im = (all_s->g_vars->zoom_y * all_s->g_vars->delta_im) - all_s->g_vars->delta_im;
	}
	else
	{
		dd_re = (all_s->g_vars->zoom_x * all_s->g_vars->delta_re) - all_s->g_vars->delta_re;
		dd_im = (all_s->g_vars->zoom_y * all_s->g_vars->delta_im) - all_s->g_vars->delta_im;
	}
	all_s->g_vars->re_min -= dd_re * x_ratio;
	all_s->g_vars->re_max += dd_re * (1 - x_ratio);
	all_s->g_vars->im_max += dd_im * y_ratio;
	all_s->g_vars->im_min -= dd_im * (1 - y_ratio);
	all_s->g_vars->delta_re = all_s->g_vars->re_max - all_s->g_vars->re_min;
	all_s->g_vars->delta_im = all_s->g_vars->im_max - all_s->g_vars->im_min;
}

void	zoom(double xdelta, double ydelta, void* context)
{
	t_all_s	*all_s = context;

	if (ydelta > 0)
	{
		all_s->g_vars->zoom_x *= 0.9;
		all_s->g_vars->zoom_y *= 0.9;
		zoom_math(all_s, 1);
	}
	else
	{
		all_s->g_vars->zoom_x *= 1.1;
		all_s->g_vars->zoom_y *= 1.1;
		zoom_math(all_s, -1);
		
	}
	make_mandel(all_s->pxl, all_s->g_vars, all_s->vars, all_s->mandel, all_s);
}

int main(int argc, char *argv[])
{
	t_img			img;
	t_mandel		mandel;
	t_vars			vars;
	t_graphic_vars	g_vars;
	t_all_s			all_s;
	t_pxl_data		*pxl;
	int				count;

	pxl = (t_pxl_data *)malloc(sizeof(t_pxl_data) * (700 * 700 + 1));
	count = 0;
	g_vars.count = 0;
	
	vars.win_height = 600;
	vars.win_width = 600;
	//g_vars.w_x = -2;
	//g_vars.w_y = -2;
	g_vars.zoom_x = 1;
	g_vars.zoom_y = 1;
	g_vars.offset_x = 2;
	g_vars.offset_y = 2;
	g_vars.delta_re = 4.0;
	g_vars.delta_im = 4.0;
	g_vars.re_min = -2;
	g_vars.re_max = 2;
	g_vars.im_max = 2;
	g_vars.im_min = -2;
	g_vars.m_sx = 0;
	g_vars.m_sy = 0;
	g_vars.m_wx_start = 0;
	g_vars.m_wy_start = 0;
	g_vars.def_scale_x = vars.win_width / 4.0;
	g_vars.def_scale_y = vars.win_height / 4.0;
	g_vars.steps_x = 4.0 / vars.win_width;
	g_vars.steps_y = 4.0 / vars.win_height;
	all_s.g_vars = &g_vars;
	all_s.pxl = pxl;
	all_s.mandel = &mandel;
	vars.mlx = mlx_init(vars.win_width, vars.win_height, "FRACTOL", 1);
	img.img = mlx_new_image(vars.mlx, vars.win_width, vars.win_height);
	all_s.img = &img;
	all_s.vars = &vars;
	if (argc > 2)
	{
		mandel.c_r = atof(argv[1]);
		mandel.c_i = atof(argv[2]);
		printf("%s\n", argv[1]);
	}
	make_mandel(pxl, &g_vars, &vars, &mandel, &all_s);
	mlx_key_hook(vars.mlx, &my_keyhook, &all_s);
	mlx_scroll_hook(vars.mlx, &zoom, &all_s);
	mlx_mouse_hook(vars.mlx, &mouse_press, &all_s);
	mlx_loop_hook(vars.mlx, &test, &all_s);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}